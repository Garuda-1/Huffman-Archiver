//
// Created by oktet on 12.06.19.
//

#include "gtest/gtest.h"
#include "../engine/huffman_engine.hpp"

#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>

template<typename input_iterator_1, typename input_iterator_2>
bool chunk_equal(input_iterator_1 begin_1, input_iterator_1 end_1,
        input_iterator_2 begin_2, input_iterator_2 end_2) {
    while (begin_1 != end_1 && begin_2 != end_2) {
        if (*begin_1 != *begin_2) {
            return false;
        }
        ++begin_1;
        ++begin_2;
    }
    return (begin_1 == end_1 && begin_2 == end_2);
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

TEST(integrity_switch, empty) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_empty";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_switch, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_switch, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_switch, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_switch, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_switch, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_switch, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}


TEST(integrity_independent, empty) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_empty";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_independent, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_independent, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_independent, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_independent, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_independent, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(integrity_independent, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}



TEST(double_integrity_switch, empty) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_empty";
    double_encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_switch, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";
    double_encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_switch, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";
    double_encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_switch, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";
    double_encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_switch, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";
    double_encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_switch, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";
    double_encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_switch, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}



TEST(double_integrity_independent, empty) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_empty";
    double_encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_independent, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";
    double_encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_independent, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";
    double_encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_independent, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";
    double_encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_independent, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";
    double_encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_independent, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";
    double_encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(double_integrity_independent, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(corrupted_input, non_existing_source_encode) {
    huffman::huffman_archiver engine("test_non_exist.in");
    EXPECT_ANY_THROW(engine.encode("test_non_exist.out"));
}

TEST(corrupted_input, non_existing_source_decode) {
    huffman::huffman_archiver engine("test_non_exist.in");
    EXPECT_ANY_THROW(engine.decode("test_non_exist.out"));
}

TEST(corrupted_input, forbidden_target_name_encode) {
    huffman::huffman_archiver engine("../testing/tests/test_small.in");
    EXPECT_ANY_THROW(engine.encode("bad/name/out"));
}

TEST(corrupted_input, forbidden_target_name_decode) {
    huffman::huffman_archiver engine("../testing/tests/test_small.in");
    EXPECT_ANY_THROW(engine.decode("bad/name/out"));
}

TEST(corrupted_input, bad_table) {
    std::string prefix = "../testing/tests/";
    std::string filename = "bad_table";
    huffman::huffman_archiver engine(prefix + filename + ".in");
    EXPECT_ANY_THROW(engine.decode(prefix + filename + ".out"));
}

TEST(corrupted_input, bad_size) {
    std::string prefix = "../testing/tests/";
    std::string filename = "bad_size";
    huffman::huffman_archiver engine(prefix + filename + ".in");
    EXPECT_ANY_THROW(engine.decode(prefix + filename + ".out"));
}

TEST(corrupted_input, bad_code) {
    std::string prefix = "../testing/tests/";
    std::string filename = "bad_code";
    huffman::huffman_archiver engine(prefix + filename + ".in");
    EXPECT_ANY_THROW(engine.decode(prefix + filename + ".out"));
}