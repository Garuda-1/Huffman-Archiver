#include "huffman_engine.hpp"
#include <limits>
#include <iostream>
#include <string>
#include <fstream>

huffman::huffman_archiver::huffman_archiver() : frequencies(std::numeric_limits<unsigned char>::max() + 1), pos(0) {}

void huffman::huffman_archiver::calculate_chunk_frequencies(char *begin, const char *end) {
    for (; begin != end; ++begin) {
        ++frequencies[static_cast<unsigned char>(*begin)];
    }
}

bool huffman::huffman_archiver::build_tree() {
    code_tree.build(frequencies);
    return code_tree.order.empty();
}

void huffman::huffman_archiver::build_table() {
    code_table = code_tree.get_code_table();
}

bool huffman::huffman_archiver::encode_chunk(char *input_begin, const char *input_end, size_t buffer_size) {
    for (; input_begin != input_end; ++input_begin) {
        huffman::bit_set code = code_table[static_cast<unsigned char>(*input_begin)];
        bitwise_buffer.append_and_flush(code, output_buffer, buffer_size);
    }
    return !output_buffer.empty();
}

void huffman::huffman_archiver::flush(std::vector<char> &dest) {
    for (char c : output_buffer) {
        dest.push_back(c);
    }
    output_buffer.resize(0);
}

void huffman::huffman_archiver::forced_flush(std::vector<char> &dest) {
    bitwise_buffer.flush(dest);
}

bool
huffman::huffman_archiver::decode_chunk(char *input_begin, const char *input_end, size_t buffer_size, uint64_t &total,
                                        uint64_t &read) {
    std::vector<char> input;
    for (; input_begin != input_end; ++input_begin) {
        input.push_back(*input_begin);
    }
    huffman::bit_set input_bitwise_buffer(input);

    for (size_t i = 0; i < input_bitwise_buffer.size(); ++i) {
        if (code_tree.order.size() == 1) {
            if (input_bitwise_buffer[i]) {
                throw std::runtime_error("Corrupted encoded file");
            }
        } else {
            if (input_bitwise_buffer[i]) {
                pos = code_tree.order[pos].r_subtree;
            } else {
                pos = code_tree.order[pos].l_subtree;
            }
            if (pos == std::numeric_limits<uint64_t>::max()) {
                throw std::runtime_error("Corrupted encoded file");
            }
        }
        if (code_tree.order[pos].chars.size() == 1) {
            --frequencies[code_tree.order[pos].chars[0]];
            output_buffer.push_back(static_cast<char>(code_tree.order[pos].chars[0]));
            pos = code_tree.order.size() - 1;
            ++read;
            if (total == read) {
                return true;
            }
        }
    }

    return output_buffer.size() >= buffer_size;
}

void huffman::huffman_archiver::reset() {
    std::fill(frequencies.begin(), frequencies.end(), 0);
    bitwise_buffer.clear();
    code_table.resize(0);
    output_buffer.resize(0);
}
