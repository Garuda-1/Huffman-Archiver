#include <iostream>
#include <cstring>
#include "../engine/huffman_engine.hpp"

int main(int32_t argc, char** argv) {
    std::string help = "\tAvailable commands:\n"
                       "\t\t--encode\t\tencode a file\n"
                       "\t\t--decode\t\tdecode a file\n"
                       "\t\t--help\t\t\tshow this menu\n";
    if (argc != 4) {
        std::cout << "Usage: huffman_archiver_app COMMAND SOURCE FILENAME\n" << help;
        return 0;
    }

    if (std::strcmp(argv[1], "--encode") == 0) {
        huffman::huffman_archiver engine(argv[2]);
        engine.encode(argv[3]);
    } else if (std::strcmp(argv[1], "--decode") == 0) {
        huffman::huffman_archiver engine(argv[2]);
        engine.decode(argv[3]);
    } else {
        std::cout << "Invalid command\n";
    }

    return 0;
}
