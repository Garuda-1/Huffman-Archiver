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
    huffman::huffman_archiver engine(prefix + name + ".in");
    engine.encode(prefix + name + ".bin");

    engine.change_source(prefix + name + ".bin");
    engine.decode(prefix + name + ".out");
}

void encode_and_decode_independent(const std::string &prefix, const std::string &name) {
    huffman::huffman_archiver engine1(prefix + name + ".in");
    engine1.encode(prefix + name + ".bin");

    huffman::huffman_archiver engine2(prefix + name + ".bin");
    engine2.decode(prefix + name + ".out");
}

void double_encode_and_decode_switch(const std::string &prefix, const std::string &name) {
    huffman::huffman_archiver engine(prefix + name + ".in");
    engine.encode(prefix + name + "_layer1.bin");

    engine.change_source(prefix + name + "_layer1.bin");
    engine.encode(prefix + name + "_layer2.bin");

    engine.change_source(prefix + name + "_layer2.bin");
    engine.decode(prefix + name + "_layer3.bin");

    engine.change_source(prefix + name + "_layer3.bin");
    engine.decode(prefix + name + "_layer4.out");
}

void double_encode_and_decode_independent(const std::string &prefix, const std::string &name) {
    huffman::huffman_archiver engine1(prefix + name + ".in");
    engine1.encode(prefix + name + "_layer1.bin");

    huffman::huffman_archiver engine2(prefix + name + "_layer1.bin");
    engine2.encode(prefix + name + "_layer2.bin");

    huffman::huffman_archiver engine3(prefix + name + "_layer2.bin");
    engine3.decode(prefix + name + "_layer3.bin");

    huffman::huffman_archiver engine4(prefix + name + "_layer3.bin");
    engine4.decode(prefix + name + "_layer4.out");
}
