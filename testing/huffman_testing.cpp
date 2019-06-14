#include <chrono>
#include "huffman_testing_aux.hpp"

/*
 * INTEGRITY TEST (SWITCH)
 *
 * Ensures that single engine perform encoding and decoding by switching target
 */

TEST(integrity_switch, empty) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_empty";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_switch, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_switch, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_switch, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_switch, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_switch, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_switch, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";
    encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

/*
 * DOUBLE INTEGRITY TEST (SWITCH)
 *
 * Ensures that single constructor can perform double encoding composition
 */

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
    double_encode_and_decode_switch(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

/*
 * PERFORMANCE TEST (ENCODING)
 *
 * Calculates encoding speed and verifies
 */

TEST(encoding_perfomance, empty) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_empty";

    auto start = std::chrono::system_clock::now();
    encode(prefix + filename + ".in", prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    decode(prefix + filename + "_perf_encode.bin", prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";

    auto start = std::chrono::system_clock::now();
    encode(prefix + filename + ".in", prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    decode(prefix + filename + "_perf_encode.bin", prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";

    auto start = std::chrono::system_clock::now();
    encode(prefix + filename + ".in", prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    decode(prefix + filename + "_perf_encode.bin", prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";

    auto start = std::chrono::system_clock::now();
    encode(prefix + filename + ".in", prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    decode(prefix + filename + "_perf_encode.bin", prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";

    auto start = std::chrono::system_clock::now();
    encode(prefix + filename + ".in", prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    decode(prefix + filename + "_perf_encode.bin", prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";

    auto start = std::chrono::system_clock::now();
    encode(prefix + filename + ".in", prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    decode(prefix + filename + "_perf_encode.bin", prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";

    auto start = std::chrono::system_clock::now();
    encode(prefix + filename + ".in", prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    decode(prefix + filename + "_perf_encode.bin", prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

/*
 * PERFORMANCE TEST (DECODING)
 *
 * Calculates decoding speed and verifies
 */

TEST(decoding_perfomance, empty) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_empty";

    encode(prefix + filename + ".in", prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    decode(prefix + filename + "_perf_decode.bin", prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";

    encode(prefix + filename + ".in", prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    decode(prefix + filename + "_perf_decode.bin", prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_pref_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";

    encode(prefix + filename + ".in", prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    decode(prefix + filename + "_perf_decode.bin", prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";

    encode(prefix + filename + ".in", prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    decode(prefix + filename + "_perf_decode.bin", prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";

    encode(prefix + filename + ".in", prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    decode(prefix + filename + "_perf_decode.bin", prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";

    encode(prefix + filename + ".in", prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    decode(prefix + filename + "_perf_decode.bin", prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(decoding_perfomance, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";

    encode(prefix + filename + ".in", prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    decode(prefix + filename + "_perf_decode.bin", prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

/*
 * CORRUPTED INPUT TEST
 *
 * Ensures throwing runtime error in case of corrupted input
 */

TEST(corrupted_input, non_existing_source_encode) {
    EXPECT_ANY_THROW(encode("test_non_exist.in", "test_non_exist.out"));
}

TEST(corrupted_input, non_existing_source_decode) {
    EXPECT_ANY_THROW(decode("test_non_exist.in", "test_non_exist.out"));
}

TEST(corrupted_input, forbidden_target_name_encode) {
    EXPECT_ANY_THROW(encode("../testing/tests/test_small.in", "bad/name/out"));
}

TEST(corrupted_input, forbidden_target_name_decode) {
    EXPECT_ANY_THROW(decode("../testing/tests/test_small.in", "bad/name/out"));
}

TEST(corrupted_input, bad_table) {
    std::string prefix = "../testing/tests/";
    std::string filename = "bad_table";
    EXPECT_ANY_THROW(decode(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(corrupted_input, bad_size) {
    std::string prefix = "../testing/tests/";
    std::string filename = "bad_size";
    EXPECT_ANY_THROW(decode(prefix + filename + ".in", prefix + filename + ".out"));
}

TEST(corrupted_input, bad_code) {
    std::string prefix = "../testing/tests/";
    std::string filename = "bad_code";
    EXPECT_ANY_THROW(decode(prefix + filename + ".in", prefix + filename + ".out"));
}
