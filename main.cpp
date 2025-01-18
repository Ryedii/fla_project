#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "automata.h"
#include "parse.h"

const std::string help_str = "usage:   fla [-h|--help] <pda> <input>"
                             "         fla [-v|--verbose] [-h|--help] <tm> <input>\n";

std::string get_file_extension(std::string& filename) {
    size_t last_dot_pos = filename.find_last_of('.');
    if (last_dot_pos == std::string::npos)
        return "";
    return filename.substr(last_dot_pos + 1);
}

int main(int argc, char *argv[]) {
    bool is_verbose = false, is_help = false;
    std::string am_path, input;
    for (int indx = 1; indx < argc; ++indx) {
        if (strcmp(argv[indx], "-v") == 0 || strcmp(argv[indx], "--verbose") == 0)
            is_verbose = true;
        else if (strcmp(argv[indx], "-v") == 0 || strcmp(argv[indx], "--help") == 0)
            is_help = true;
        else if (am_path.empty())
            am_path = argv[indx];
        else if (input.empty())
            input = argv[indx];
        else
            break;
    }

    if (1 + is_verbose + is_help + 2 != argc || am_path.empty() || input.empty() || is_help) {
        std::cerr << help_str << std::endl;
        return 0;
    }

    std::fstream am_file(am_path);
    if (!am_file.is_open()) {
        std::cerr << "File " << am_path << " not be open." << std::endl;
        exit(-1);
    }

    std::string file_ext = get_file_extension(am_path);
    int am_type = -1;
    if (file_ext == "pda")
        am_type = 1;
    if (file_ext == "tm")
        am_type = 2;
    if (am_type == -1) {
        std::cerr << "File " << am_path << " not be recognised." << std::endl;
        exit(-1);
    }

    if (am_type == 1) {
        PDA pda;
        int err = 0;
        err = read(am_file, pda);
    }
    if (am_type == 2) {

    }
    tm = parser(argv[ind]);
    if (!tm.has_value())exit(-1);
    tm->init();
    if (is_verbose) std::cout << "Input: " << argv[ind + 1] << std::endl;
    if (uint32_t code = tm->loadInput(argv[ind + 1]); code > 0
    ) {
        if (is_verbose) {
            std::cerr << "==================== ERR ====================\n";
            std::cerr << "error: Symbol \"" << argv[ind + 1][code - 1] <<
                    "\" in input is not defined in the set of input symbols\n";
            std::cerr << "Input: " << argv[ind + 1] << std::endl;
            std::cerr << std::string(7 + code - 1, ' ') << "^\n";
            std::cout << "==================== END ====================\n";
        } else std::cerr << "illegal input string\n";
        return -1;
    }
    else
    if (is_verbose) {
        std::cout << "==================== RUN ====================\n";
        std::cout << tm->ID();
        std::cout << "---------------------------------------------\n";
        while (tm->move()) {
            std::cout << tm->ID();
            std::cout << "---------------------------------------------\n";
        }
        std::cout << tm->result(true);
        std::cout << "==================== END ====================\n";
    } else {
        tm->run();
        std::cout << tm->result(false) << std::endl;
    }
    return 0;
}
