cmake_minimum_required(VERSION 3.13)
project(Huffman_Archiver)

set(CMAKE_CXX_STANDARD 17)

set(ENGINE_FILES
        engine/huffman_engine_archiver.cpp
        engine/huffman_engine.hpp
        engine/huffman_engine_tree.cpp
        engine/huffman_engine_bitset.cpp)
set(UTILITY_FILES
        utility/archiver_utility.cpp)
set(UNIT_TESTING_FILES
        unit_testing.cpp)
set(TESTING_FILES
        testing/gtest/gtest-all.cc
        testing/gtest/gtest.h
        testing/gtest/gtest_main.cc
        testing/huffman_testing.cpp testing/huffman_testing_aux.hpp testing/huffman_testing_aux.cpp)

add_library(huffman_archiver_engine STATIC ${ENGINE_FILES})
add_executable(archiver_utility ${UTILITY_FILES})
add_executable(huffman_unit_testing ${UNIT_TESTING_FILES})
add_executable(huffman_testing ${TESTING_FILES})

target_link_libraries(archiver_utility huffman_archiver_engine)
target_link_libraries(huffman_unit_testing huffman_archiver_engine)
target_link_libraries(huffman_testing pthread huffman_archiver_engine)