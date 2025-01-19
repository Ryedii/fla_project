#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "automata.h"
#include "parse.h"

const std::string help_str = "usage:   fla [-h|--help] <pda> <input>\n"
        "         fla [-v|--verbose] [-h|--help] <tm> <input>\n";

std::string get_file_extension(std::string &filename) {
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
        else if (strcmp(argv[indx], "-h") == 0 || strcmp(argv[indx], "--help") == 0)
            is_help = true;
        else if (am_path.empty())
            am_path = argv[indx];
        else if (input.empty())
            input = argv[indx];
        else
            break;
    }

    if (3 + is_verbose + is_help != argc || am_path.empty() || input.empty() || is_help) {
        std::cerr << help_str << std::endl;
        return 0;
    }

    std::ifstream am_file(am_path);
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
    // std::cerr << "debug@main: #1 am_type = " << am_type << std::endl;

    if (am_type == 1) {
        PDA pda;
        int err = 0;
        err = read(am_file, pda);
        // std::cerr << "debug@main: #2 read err = " << err << std::endl;
        if (err != 0) {
            std::cerr << "syntax error" << std::endl;
            exit(1);
        }

        PDA_runner runner(&pda);
        err = runner.set_input(input);
        if (err != 0) exit(-1);
        // std::cerr << "debug@main: #3 set_input done" << std::endl;

        bool accept = false;
        err = 1;
        while (err == 1) {
            err = runner.step();
            if (err == -1)
                exit(-1);
            if (err == 0)
                accept = false;
            if (err == 1 && is_verbose)
                runner.print();
            if (err == 2)
                accept = runner.if_final();
            // std::cerr << "debug@main: #4 step err = " << err << std::endl;
            // std::cerr << "debug@main: #4 step err = " << err << " if_final = " << runner.if_final() << std::endl;
        }
        std::cerr << (accept ? "true" : "false") << std::endl;
    }

    if (am_type == 2) {
        TM tm;
        int err = 0;
        err = read(am_file, tm);
        if (err != 0) {
            std::cerr << "syntax error" << std::endl;
            exit(1);
        }

        TM_runner runner(&tm);
        err = runner.set_input(input);
        if (err != 0) exit(-1);

        while (err == 1) {
            err = runner.step();
        }
    }


    return 0;
}
