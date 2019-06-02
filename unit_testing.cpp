#include <iostream>
#include <string>
#include <bitset>
#include "engine/huffman_engine.hpp"

void input_table_test() {
    huffman::huffman_archiver archiver("test.txt");
    archiver.encode("encode.bin");
}

void bit_set_test() {
    size_t size;
    std::cin >> size;

    huffman::bit_set target(size);
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "set") {
            size_t pos;
            bool value;
            std::cin >> pos >> value;
            target.set(pos, value);
        }
        if (cmd == "get") {
            for (size_t i = 0; i < target.size(); i++) {
                std::cout << target[i];
            }
            std::cout << std::endl;
        }
        if (cmd == "pb") {
            bool value;
            std::cin >> value;
            target.push_back(value);
        }
        if (cmd == "resize") {
            size_t new_size;
            std::cin >> new_size;
            target.resize(new_size);
        }
    }
}

void bit_set_flush_test() {
    size_t flush_size;
    std::cin >> flush_size;
    huffman::bit_set target;

    std::vector<char> output;
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "get") {
            for (size_t i = 0; i < target.size(); i++) {
                std::cout << target[i];
            }
            std::cout << std::endl;
        }
        if (cmd == "append") {
            std::string operand_str;
            std::cin >> operand_str;
            huffman::bit_set operand;
            for (char i : operand_str) {
                operand.push_back(i == '1');
            }
            target.append_and_flush(operand, output, flush_size);
        }
        if (cmd == "output") {
            for (char byte : output) {
                std::cout << std::bitset<8>(byte) << "\t" << byte << "\n";
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: huffman_unit_testing [--encode]" << std::endl;
        return 0;
    }
    std::string section(argv[1]);
    if (section == "--encode") {
        input_table_test();
    }
    if (section == "--bit_set") {
        bit_set_test();
    }
    if (section == "--bit_set_flush") {
        bit_set_flush_test();
    }
}