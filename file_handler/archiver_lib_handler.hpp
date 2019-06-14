#ifndef HUFFMAN_ARCHIVER_ARCHIVER_LIB_HANDLER_HPP
#define HUFFMAN_ARCHIVER_ARCHIVER_LIB_HANDLER_HPP

#include "../engine/huffman_engine.hpp"
#include <fstream>

void read_chunk_from_file(std::ifstream &input_file_stream, std::vector<char> &input_buffer, size_t input_buffer_size);
void write_frequencies_to_file(std::ofstream &output_file_stream, std::vector<uint64_t> frequencies);
uint64_t read_uint64_t(std::ifstream &input_file_stream);

void encode(std::string src, std::string target);
void decode(std::string src, std::string target);

#endif
