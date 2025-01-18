#include "parse.h"
#include "automata.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

std::vector<std::string> scan(std::string line, char c = 0, char l = 0, char r = 0) {
    std::vector<std::string> words;
    int m = 0, n;
    if (l != 0) {
        int n = line.find(r);
        if (n == std::string::npos)
            return words;
        m = line.find(l, 0);
    } else
        n = line.size();
    for (int i = m, j; i < n; i = j) {
        j = line.find(c, i + 1);
        if (j > i)
            words.push_back(line.substr(i + 1, j));
    }
    return words;
}

int read(std::ifstream &file, PDA &p) {
    std::string line;
    p.clear();
    while (getline(file, line)) {
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
            if (line[1] == 'q') {
                std::vector<std::string> words = scan(line);
                int err = p.set_start_state(words[0]);
                if (err != 0) return err;
            }
            if (line[1] == 'z') {
                std::vector<std::string> words = scan(line);
                int err = p.set_start_symbol(words[0]);
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
}

