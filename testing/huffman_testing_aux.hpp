#include "gtest/gtest.h"
#include "../engine/huffman_engine.hpp"
#include "../file_handler/archiver_lib_handler.hpp"

#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>

#ifndef HUFFMAN_ARCHIVER_HUFFMAN_TESTING_AUX_HPP
#define HUFFMAN_ARCHIVER_HUFFMAN_TESTING_AUX_HPP

namespace testing::internal {
    enum GTestColor {
        COLOR_DEFAULT,
        COLOR_RED,
        COLOR_GREEN,
        COLOR_YELLOW
    };

    extern void ColoredPrintf(GTestColor color, const char *fmt, ...);
}

#define PRINTF(...)  \
    do { \
        testing::internal::ColoredPrintf(testing::internal::COLOR_GREEN, "[          ] "); \
        testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, __VA_ARGS__); \
    } while(0)

class TestCout : public std::stringstream {
public:
    ~TestCout() {
        PRINTF("%s", str().c_str());
    }
};

#define TEST_COUT  TestCout()



std::ifstream::pos_type filesize(const std::string& filename);

double compression_rate(std::string &prefix, std::string &filename);

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

bool files_equal(const std::string &target_1, const std::string &target_2);

void encode_and_decode_switch(const std::string &prefix, const std::string &name);
void double_encode_and_decode_switch(const std::string &prefix, const std::string &name);


#endif
