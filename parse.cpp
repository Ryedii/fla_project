#include "parse.h"
#include "automata.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

std::vector<std::string> scan(std::string line, char c = 0, char l = 0, char r = 0) {
    std::vector<std::string> words;
    if (l != 0) {
        int n = line.find(r);
        if (n == std::string::npos)
            return words;
        int m = line.find(l, 0);
        for (int i = m, j; i < n; i = j) {
            j = line.find(c, i + 1);
            if (j == std::string::npos)
                j = n;
            if (j - i - 1 > 0)
                words.push_back(line.substr(i + 1, j - i - 1));
        }
    } else {
        line.insert(line.begin(), ' ');
        line.push_back(' ');
        for (int i = 0, j; i < line.size(); i = j) {
            j = line.find(' ', i + 1);
            if (j - i - 1 > 0)
                words.push_back(line.substr(i + 1, j - i - 1));
        }
    }
    return words;
}

int read(std::ifstream &file, PDA &p) {
    std::string line;
    p.clear();
    while (getline(file, line)) {
        int pos_semicolon = line.find(';');
        if (pos_semicolon != std::string::npos)
            line = line.substr(0, pos_semicolon);
        if (line.empty() || line[0] == ';')
            continue;
        if (line[0] == '#') {
            if (line.size() == 1)
                return -1;
            if (line[1] == 'Q') {
                std::vector<std::string> words = scan(line, ',', '{', '}');
                int err = p.set_states(words);
                if (err != 0) return err;
            }
            if (line[1] == 'S') {
                std::vector<std::string> words = scan(line, ',', '{', '}');
                int err = p.set_input_alphabet(words);
                if (err != 0) return err;
            }
            if (line[1] == 'G') {
                std::vector<std::string> words = scan(line, ',', '{', '}');
                int err = p.set_stack_alphabet(words);
                if (err != 0) return err;
            }
            if (line[1] == 'q') {
                std::vector<std::string> words = scan(line);
                int err = p.set_start_state(words[2]);
                if (err != 0) return err;
            }
            if (line[1] == 'z') {
                std::vector<std::string> words = scan(line);
                int err = p.set_start_symbol(words[2]);
                if (err != 0) return err;
            }
            if (line[1] == 'F') {
                std::vector<std::string> words = scan(line, ',', '{', '}');
                int err = p.set_final_states(words);
                if (err != 0) return err;
            }
        } else {
            std::vector<std::string> words = scan(line);
            int err = p.add_rule(words);
            if (err != 0) return err;
        }
    }
    return 0;
}

int read(std::ifstream &file, TM &t) {
    std::string line;
    t.clear();
    while (getline(file, line)) {
        // std::cerr << "debug@read: line = | " << line << std::endl;
        int pos_semicolon = line.find(';');
        if (pos_semicolon != std::string::npos)
            line = line.substr(0, pos_semicolon);
        if (line.empty() || line[0] == ';')
            continue;
        if (line[0] == '#') {
            if (line.size() == 1)
                return -1;
            if (line[1] == 'Q') {
                std::vector<std::string> words = scan(line, ',', '{', '}');
                int err = t.set_states(words);
                if (err != 0) return err;
            }
            if (line[1] == 'S') {
                std::vector<std::string> words = scan(line, ',', '{', '}');
                int err = t.set_input_alphabet(words);
                if (err != 0) return err;
            }
            if (line[1] == 'G') {
                std::vector<std::string> words = scan(line, ',', '{', '}');
                int err = t.set_tape_alphabet(words);
                if (err != 0) return err;
            }
            if (line[1] == 'q') {
                std::vector<std::string> words = scan(line);
                int err = t.set_start_state(words[2]);
                if (err != 0) return err;
            }
            if (line[1] == 'B') {
                std::vector<std::string> words = scan(line);
                if (words[2] != "_") return -1;
            }
            if (line[1] == 'F') {
                std::vector<std::string> words = scan(line, ',', '{', '}');
                int err = t.set_final_states(words);
                if (err != 0) return err;
            }
            if (line[1] == 'N') {
                std::vector<std::string> words = scan(line);
                int err = t.set_tape_num(words[2]);
                if (err != 0) return err;
            }
        } else {
            std::vector<std::string> words = scan(line);
            int err = t.add_rule(words);
            if (err != 0) return err;
        }
    }
    return 0;
}


