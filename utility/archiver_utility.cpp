#include <iostream>
#include <cstring>
#include "../file_handler/archiver_lib_handler.hpp"


int main(int32_t argc, char** argv) {
    std::string help = "\tAvailable commands:\n"
                       "\t\t--encode\t\tencode a file\n"
                       "\t\t--decode\t\tdecode a file\n"
                       "\t\t--help\t\t\tshow this menu\n";

    if (argc != 4) {
        if (argc == 2 && std::strcmp(argv[1], "--help") == 0) {
            std::cout << help;
        } else {
            std::cout << "Usage: archiver_utility COMMAND [SOURCE FILENAME]\n" << help;
        }
        return 0;
    }

    if (std::strcmp(argv[1], "--encode") == 0) {
        try {
            encode(argv[2], argv[3]);
        } catch (std::runtime_error &e) {
            std::cout << "Encoding error: \n\t" << e.what() << '\n';
        }
    } else if (std::strcmp(argv[1], "--decode") == 0) {
        try {
            decode(argv[2], argv[3]);
        } catch (std::runtime_error &e) {
            std::cout << "Decoding error: \n\t" << e.what() << '\n';
        }
    } else {
        std::cout << "Invalid command\n";
    }

    return 0;
}
