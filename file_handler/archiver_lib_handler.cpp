#include "archiver_lib_handler.hpp"


void read_chunk_from_file(std::ifstream &input_file_stream, std::vector<char> &input_buffer,
                          size_t input_buffer_size) {
    input_buffer.resize(input_buffer_size);
    input_file_stream.read(input_buffer.data(), input_buffer_size);
    input_buffer.resize(input_file_stream.gcount());
}

void write_frequencies_to_file(std::ofstream &output_file_stream, std::vector<uint64_t> frequencies) {
    for (unsigned long & frequency : frequencies) {
        output_file_stream.write((char*) (&frequency), sizeof(frequency) / sizeof(char));
    }
}

uint64_t read_uint64_t(std::ifstream &input_file_stream) {
    uint64_t res = 0;
    size_t request_size = sizeof(uint64_t) / sizeof(char);
    input_file_stream.read((char*) (&res), request_size);
    if (static_cast<size_t>(input_file_stream.gcount()) != request_size) {
        input_file_stream.close();
        throw std::runtime_error("Corrupted encoded file");
    }
    return res;
}

void encode(const std::string src, const std::string target) {
    size_t buffer_size = 16;

    std::ifstream input_file_stream_freq(src, std::ios::binary);
    if (!input_file_stream_freq.is_open()) {
        throw std::runtime_error("Input file opening failure");
    }
    huffman::huffman_archiver engine;
    std::vector<char> input_buffer;

    do {
        read_chunk_from_file(input_file_stream_freq, input_buffer, buffer_size);
        engine.calculate_chunk_frequencies(input_buffer.data(), input_buffer.data() + input_buffer.size());
    } while (input_buffer.size() == buffer_size);

    input_file_stream_freq.close();

    engine.build_tree();
    engine.build_table();

    std::ifstream input_file_stream(src, std::ios::binary);
    if (!input_file_stream.is_open()) {
        throw std::runtime_error("Input file opening failure");
    }
    std::ofstream output_file_stream(target, std::ios::binary);
    if (!output_file_stream.is_open()) {
        input_file_stream.close();
        throw std::runtime_error("Output file opening failure");
    }

    write_frequencies_to_file(output_file_stream, engine.frequencies);
    std::vector<char> output_buffer;

    do {
        read_chunk_from_file(input_file_stream, input_buffer, buffer_size);
        bool ready = engine.encode_chunk(input_buffer.data(), input_buffer.data() + input_buffer.size(), buffer_size);
        if (ready) {
            engine.flush(output_buffer);
            output_file_stream.write(output_buffer.data(), output_buffer.size());
            output_buffer.resize(0);
        }
    } while (input_buffer.size() == buffer_size);

    engine.forced_flush(output_buffer);
    output_file_stream.write(output_buffer.data(), output_buffer.size());

    input_file_stream.close();
    output_file_stream.close();
    engine.reset();
}

void decode(const std::string src, const std::string target) {
    size_t buffer_size = 16;

    std::ifstream input_file_stream(src, std::ios::in | std::ios::binary);
    if (!input_file_stream.is_open()) {
        throw std::runtime_error("Input file opening failure");
    }

    huffman::huffman_archiver engine;
    std::vector<char> input_buffer;

    for (uint64_t & frequency : engine.frequencies) {
        frequency = read_uint64_t(input_file_stream);
    }

    std::ofstream output_file_stream(target, std::ios::out | std::ios::binary);
    if (!output_file_stream.is_open()) {
        input_file_stream.close();
        throw std::runtime_error("Output file opening failure");
    }

    if (engine.build_tree()) {
        input_file_stream.close();
        output_file_stream.close();
        return;
    }
    engine.pos = engine.code_tree.order.size() - 1;
    uint64_t total = engine.code_tree.order[engine.pos].freq;
    uint64_t read = 0;
    std::vector<char> output_buffer;

    do {
        read_chunk_from_file(input_file_stream, input_buffer, buffer_size);
        bool ready = engine.decode_chunk(input_buffer.data(), input_buffer.data() + input_buffer.size(), buffer_size, total,
                                         read);
        if (ready) {
            engine.flush(output_buffer);
            output_file_stream.write(output_buffer.data(), output_buffer.size());
            output_buffer.resize(0);
        }
    } while (input_buffer.size() == buffer_size && read < total);

    bool all_read = true;
    for (auto frequency : engine.frequencies) {
        if (frequency != 0) {
            all_read = false;
            break;
        }
    }
    if (!all_read || read != total) {
        input_file_stream.close();
        output_file_stream.close();
        throw std::runtime_error("Corrupted encoded file");
    }

    output_file_stream.write(output_buffer.data(), output_buffer.size());

    input_file_stream.close();
    output_file_stream.close();
    engine.reset();
}
