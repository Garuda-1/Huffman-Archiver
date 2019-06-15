cmake_minimum_required(VERSION 3.13)
project(Huffman_Archiver)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined -fsanitize=address -fsanitize=leak -Wall -std=c++11 -pedantic -D_GLIBCXX_DEBUG")
endif()

set(ENGINE_FILES
        engine/huffman_engine_archiver.cpp
        engine/huffman_engine.hpp
        engine/huffman_engine_tree.cpp
        engine/huffman_engine_bitset.cpp)
set(UTILITY_FILES
        utility/archiver_utility.cpp
        file_handler/archiver_lib_handler.hpp
        file_handler/archiver_lib_handler.cpp)
set(TESTING_FILES
        testing/gtest/gtest-all.cc
        testing/gtest/gtest.h
        testing/gtest/gtest_main.cc

        testing/huffman_testing.cpp

        file_handler/archiver_lib_handler.hpp
        file_handler/archiver_lib_handler.cpp

        testing/huffman_testing_aux.hpp
        testing/huffman_testing_aux.cpp)

add_library(huffman_archiver_engine STATIC ${ENGINE_FILES})
add_executable(archiver_utility ${UTILITY_FILES})
add_executable(huffman_testing ${TESTING_FILES})

target_link_libraries(archiver_utility huffman_archiver_engine)
target_link_libraries(huffman_testing pthread huffman_archiver_engine)