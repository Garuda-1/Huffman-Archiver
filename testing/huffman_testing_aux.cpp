#include "huffman_testing_aux.hpp"


std::ifstream::pos_type filesize(const std::string& filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

double compression_rate(std::string &prefix, std::string &filename) {
    return static_cast<double>(filesize(prefix + filename + ".bin")) /
           static_cast<double>(filesize(prefix + filename + ".in"));
}

bool files_equal(const std::string &target_1, const std::string &target_2) {
    std::ifstream in_1(target_1, std::ios::binary);
    std::ifstream in_2(target_2, std::ios::binary);

    if (!in_1.is_open() || !in_2.is_open()) {
        throw std::runtime_error("Unable to open one of the files");
    }

    std::istreambuf_iterator<char> begin_1(in_1);
    std::istreambuf_iterator<char> begin_2(in_2);

    std::istreambuf_iterator<char> end;
    return chunk_equal(begin_1, end, begin_2, end);
}

void encode_and_decode_switch(const std::string &prefix, const std::string &name) {
    encode(prefix + name + ".in", prefix + name + ".bin");
    decode(prefix + name + ".bin", prefix + name + ".out");
}

void double_encode_and_decode_switch(const std::string &prefix, const std::string &name) {
    encode(prefix + name + ".in", prefix + name + "_l1.bin");
    encode(prefix + name + "_l1.bin", prefix + name + "_l2.bin");
    decode(prefix + name + "_l2.bin", prefix + name + "_l3.bin");
    decode(prefix + name + "_l3.bin", prefix + name + ".out");
}
