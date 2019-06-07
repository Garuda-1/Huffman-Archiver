#include "huffman_engine.hpp"
#include <iostream>
#include <string>
#include <fstream>

uint64_t huffman::huffman_archiver::read_uint64_t(std::ifstream &input_file_stream) {
    uint64_t res = 0;
    size_t request_size = sizeof(uint64_t) / sizeof(char);
    input_file_stream.read((char*) (&res), request_size);
    if (input_file_stream.gcount() != request_size) {
        input_file_stream.close();
        throw std::runtime_error("Corrupted encoded file");
    }
    return res;
}

void huffman::huffman_archiver::calculate_file_frequecies(const std::string &input_file_path) {
    std::ifstream input_file_stream(input_file_path);
    std::vector<char> input_buffer;
    if (!input_file_stream.is_open()) {
        throw std::runtime_error("Source file opening failure");
    }
    do {
        read_chunk_from_file(input_file_stream, input_buffer);
        calculate_chunk_frequencies(input_buffer.data(), input_buffer.data() + input_buffer.size());
    } while (input_buffer.size() == buffer_max_size);
}

void huffman::huffman_archiver::calculate_chunk_frequencies(char *begin, const char *end) {
    for (; begin != end; ++begin) {
        ++frequencies[static_cast<unsigned char>(*begin)];
    }
}

void
huffman::huffman_archiver::read_chunk_from_file(std::ifstream &input_file_stream, std::vector<char> &input_buffer) {
    input_buffer.resize(buffer_max_size);
    input_file_stream.read(input_buffer.data(), buffer_max_size);
    input_buffer.resize(input_file_stream.gcount());
}

huffman::huffman_archiver::huffman_archiver(std::string source_file_path)
        : source_file_path(std::move(source_file_path)), version(1) {
    frequencies.resize(charcode_range);
}

void huffman::huffman_archiver::cross_encode_file(const std::string &input_file_path,
                                                  const std::string &output_file_path, const std::vector<huffman::bit_set> &table) {
    huffman::bit_set bitwise_buffer;
    std::vector<char> write_buffer;

    std::ifstream input_file_stream(input_file_path, std::ios::in | std::ios::binary);
    if (!input_file_stream.is_open()) {
        throw std::runtime_error("Source file opening failure");
    }
    std::ofstream output_file_stream(output_file_path, std::ios::out | std::ios::binary);
    if (!output_file_stream.is_open()) {
        input_file_stream.close();
        throw std::runtime_error("Target file creation failure");
    }

    write_version_to_file(output_file_stream);
    write_frequencies_to_file(output_file_stream);
    std::vector<char> input_buffer;

    do {
        read_chunk_from_file(input_file_stream, input_buffer);
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
    tree t(frequencies);
    auto table = t.get_code_table();
    cross_encode_file(source_file_path, target_path, table);
}

void huffman::huffman_archiver::cross_decode_file(std::ifstream &input_file_stream, const std::string &target_path) {
    tree t(frequencies);

    std::ofstream output_file_stream(target_path, std::ios::out);
    if (t.order.empty()) {
        return;
    }

    std::vector<char> output_buffer;
    size_t pos = t.order.size() - 1;

    size_t decoded = 0;
    size_t total = t.order[pos].freq;
    std::vector<char> input_buffer;

    do {
        read_chunk_from_file(input_file_stream, input_buffer);
        huffman::bit_set input_bitwise_buffer(input_buffer);
        for (size_t i = 0; i < input_bitwise_buffer.size(); ++i) {
            if (t.order.size() == 1) {
                if (input_bitwise_buffer[i]) {
                    input_file_stream.close();
                    output_file_stream.close();
                    throw std::runtime_error("Corrupted encoded file");
                }
            } else {
                if (input_bitwise_buffer[i]) {
                    pos = t.order[pos].r_subtree;
                } else {
                    pos = t.order[pos].l_subtree;
                }
                if (pos == std::numeric_limits<uint64_t>::max()) {
                    input_file_stream.close();
                    output_file_stream.close();
                    throw std::runtime_error("Corrupted encoded file");
                }
            }
            if (t.order[pos].chars.size() == 1) {
                output_buffer.push_back(static_cast<char>(t.order[pos].chars[0]));

                decoded++;
                if (decoded == total) {
                    break;
                }

                if (output_buffer.size() >= buffer_max_size) {
                    output_file_stream.write(output_buffer.data(), output_buffer.size());
                    output_buffer.clear();
                    output_buffer.resize(0);
                }
                pos = t.order.size() - 1;
            }
        }
    } while (input_buffer.size() == buffer_max_size);

    if (decoded != total) {
        input_file_stream.close();
        output_file_stream.close();
        throw std::runtime_error("Corrupted encoded file");
    }

    output_file_stream.write(output_buffer.data(), output_buffer.size());

    output_file_stream.close();
}

void huffman::huffman_archiver::decode(const std::string &target_path) {
    std::ifstream input_file_stream(source_file_path, std::ios::in | std::ios::binary);
    if (!input_file_stream.is_open()) {
        throw std::runtime_error("Source file opening failure");
    }
    uint64_t target_version = read_uint64_t(input_file_stream);
    if (target_version != version) {
        input_file_stream.close();
        throw std::runtime_error("Source file version does not match archiver build version");
    }
    for (uint64_t & frequency : frequencies) {
        frequency = read_uint64_t(input_file_stream);
    }

    cross_decode_file(input_file_stream, target_path);

    input_file_stream.close();
}

void huffman::huffman_archiver::change_source(const std::string &new_source_file_path) {
    source_file_path = new_source_file_path;
}
