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
 * INTEGRITY TEST (INDEPENDENT)
 *
 * Ensures that file encoded by one engine can be decoded by another
 */

TEST(integrity_independent, empty) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_empty";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_independent, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_independent, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_independent, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_independent, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_independent, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";
    encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
    TEST_COUT << "Compression rate = " << compression_rate(prefix, filename) << '\n';
}

TEST(integrity_independent, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";
    encode_and_decode_independent(prefix, filename);
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
    double_encode_and_decode_independent(prefix, filename);
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + ".out"));
}

/*
 * DOUBLE INTEGRITY TEST (INDEPENDENT)
 *
 * Ensures that double encoding composition can be handled by 4 independent engines
 */

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
    double_encode_and_decode_independent(prefix, filename);
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
    huffman::huffman_archiver engine(prefix + filename + ".in");

    auto start = std::chrono::system_clock::now();
    engine.encode(prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    engine.change_source(prefix + filename + "_perf_encode.bin");
    engine.decode(prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    auto start = std::chrono::system_clock::now();
    engine.encode(prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    engine.change_source(prefix + filename + "_perf_encode.bin");
    engine.decode(prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    auto start = std::chrono::system_clock::now();
    engine.encode(prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    engine.change_source(prefix + filename + "_perf_encode.bin");
    engine.decode(prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    auto start = std::chrono::system_clock::now();
    engine.encode(prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    engine.change_source(prefix + filename + "_perf_encode.bin");
    engine.decode(prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    auto start = std::chrono::system_clock::now();
    engine.encode(prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    engine.change_source(prefix + filename + "_perf_encode.bin");
    engine.decode(prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    auto start = std::chrono::system_clock::now();
    engine.encode(prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    engine.change_source(prefix + filename + "_perf_encode.bin");
    engine.decode(prefix + filename + "_perf_encode.out");

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + ".in"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(encoding_perfomance, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    auto start = std::chrono::system_clock::now();
    engine.encode(prefix + filename + "_perf_encode.bin");
    auto end = std::chrono::system_clock::now();

    engine.change_source(prefix + filename + "_perf_encode.bin");
    engine.decode(prefix + filename + "_perf_encode.out");

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
    huffman::huffman_archiver engine(prefix + filename + ".in");

    engine.encode(prefix + filename + "_perf_decode.bin");
    engine.change_source(prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    engine.decode(prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, small) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_small";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    engine.encode(prefix + filename + "_perf_decode.bin");
    engine.change_source(prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    engine.decode(prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_pref_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, allbytes) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_allbytes";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    engine.encode(prefix + filename + "_perf_decode.bin");
    engine.change_source(prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    engine.decode(prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, singlebyte_zero) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_zero";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    engine.encode(prefix + filename + "_perf_decode.bin");
    engine.change_source(prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    engine.decode(prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, singlebyte_255) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_singlebyte_255";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    engine.encode(prefix + filename + "_perf_decode.bin");
    engine.change_source(prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    engine.decode(prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_decode.out"));
}

TEST(decoding_perfomance, big) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_big";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    engine.encode(prefix + filename + "_perf_decode.bin");
    engine.change_source(prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    engine.decode(prefix + filename + "_perf_decode.out");
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration(end - start);
    double size = static_cast<double>(filesize(prefix + filename + "_perf_decode.bin"));
    TEST_COUT << "Speed = " << size / duration.count() / 1024 / 1024 << " MB/S\n";
    EXPECT_TRUE(files_equal(prefix + filename + ".in", prefix + filename + "_perf_encode.out"));
}

TEST(decoding_perfomance, music) {
    std::string prefix = "../testing/tests/";
    std::string filename = "test_music";
    huffman::huffman_archiver engine(prefix + filename + ".in");

    engine.encode(prefix + filename + "_perf_decode.bin");
    engine.change_source(prefix + filename + "_perf_decode.bin");

    auto start = std::chrono::system_clock::now();
    engine.decode(prefix + filename + "_perf_decode.out");
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
