#include <utility>

#include "huffman_engine.hpp"
#include <iostream>
#include <string>
#include <fstream>

void huffman::huffman_archiver::calculate_file_frequecies(const std::string &input_file_path) {
    std::ifstream input_file_stream(input_file_path);
    do {
        read_chunk_from_file(input_file_stream);
        calculate_chunk_frequencies(input_buffer.data(), input_buffer.data() + input_buffer.size());
    } while (input_buffer.size() == buffer_max_size);
}

void huffman::huffman_archiver::calculate_chunk_frequencies(char *begin, const char *end) {
    for (; begin != end; ++begin) {
        ++frequencies[static_cast<unsigned char>(*begin)];
    }
}

void huffman::huffman_archiver::read_chunk_from_file(std::ifstream &input_file_stream) {
    input_buffer.resize(buffer_max_size);
    input_file_stream.read(input_buffer.data(), buffer_max_size);
    input_buffer.resize(input_file_stream.gcount());
}

huffman::huffman_archiver::huffman_archiver(std::string source_file_path)
        : source_file_path(std::move(source_file_path)), version(1) {
    frequencies.resize(charcode_range);
    input_buffer.resize(buffer_max_size);
}

void huffman::huffman_archiver::cross_encode_file(const std::string &input_file_path,
                                                  const std::string &output_file_path, const std::vector<huffman::bit_set> &table) {
    huffman::bit_set bitwise_buffer;
    std::vector<char> write_buffer;

    std::ifstream input_file_stream(input_file_path, std::ios::in | std::ios::binary);
    if(!input_file_stream.is_open()) {
        std::cout << "CROSS_ENCODING: file opening failure!\n";
        return;
    }
    std::ofstream output_file_stream(output_file_path, std::ios::out | std::ios::binary);
    if(!output_file_stream.is_open()) {
        std::cout << "CROSS_ENCODING: file opening failure!\n";
        input_file_stream.close();
        return;
    }

    write_version_to_file(output_file_stream);
    write_frequencies_to_file(output_file_stream);

    do {
        read_chunk_from_file(input_file_stream);
        for (char c : input_buffer) {
            huffman::bit_set code = table[static_cast<unsigned char>(c)];
            bitwise_buffer.append_and_flush(code, write_buffer, buffer_max_size);
            if (write_buffer.size() > buffer_max_size) {
                output_file_stream.write(write_buffer.data(), write_buffer.size());
                write_buffer.clear();
                write_buffer.resize(0);
            }
        }
    } while (input_buffer.size() == buffer_max_size);

    bitwise_buffer.flush(write_buffer);
    output_file_stream.write(write_buffer.data(), write_buffer.size());

    input_file_stream.close();
    output_file_stream.close();
}

void huffman::huffman_archiver::write_version_to_file(std::ofstream &output_file_stream) {
    output_file_stream.write((char*) (&version), sizeof(version) / sizeof(char));
}

void huffman::huffman_archiver::write_frequencies_to_file(std::ofstream &output_file_stream) {
    for (unsigned long & frequency : frequencies) {
        output_file_stream.write((char*) (&frequency), sizeof(frequency) / sizeof(char));
    }
}

void huffman::huffman_archiver::encode(const std::string &target_path) {
    calculate_file_frequecies(source_file_path);
    for (size_t i = 0; i < charcode_range; ++i) {
        std::cout << i << '\t' << frequencies[i] << '\n';
    }
    tree t(frequencies);
    for (huffman::tree::tree_node &v : t.order) {
        std::string set;
        for (unsigned char c : v.chars) {
            set += static_cast<char>(c);
        }
        std::cout << "l=" << v.l_subtree << "; r=" << v.r_subtree << "; set=" << set << "; freq=" << v.freq << "\n";
    }
    auto table = t.get_code_table();
    for (unsigned char i = 0; i < std::numeric_limits<unsigned char>::max(); ++i) {
        if (table[i].size() != 0) {
            std::cout << static_cast<char>(i) << "=" << to_string(table[i]) << "\n";
        }
    }
    cross_encode_file(source_file_path, target_path, table);
}


