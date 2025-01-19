#include "automata.h"
#include <algorithm>
#include <complex.h>
#include <cstring>
#include <iostream>
#include <ostream>

int Automata::set_states(const std::vector<std::string> &s) {
    if (!states.empty())
        return -1;
    for (const auto &s: s)
        states.push_back(s);
    return 0;
}

int Automata::set_input_alphabet(const std::vector<std::string> &s) {
    if (!input_alphabet.empty())
        return -1;
    for (const auto &s: s)
        input_alphabet.push_back(s[0]);
    return 0;
}

int Automata::set_start_state(const std::string &s) {
    if (start_state != -1)
        return -1;
    start_state = find_state(s);
    if (start_state == -1)
        return -1;
    return 0;
}

int Automata::set_final_states(const std::vector<std::string> &s) {
    for (const auto &s: s) {
        int indx = find_state(s);
        if (indx == -1)
            return -1;
        states[indx].is_final = true;
    }
    return 0;
}

void Automata::clear() {
    states.clear();
    start_state = -1;
    input_alphabet.clear();
}

int Automata::find_state(const std::string &s) {
    for (int i = 0; i < states.size(); ++i)
        if (s == states[i].name)
            return i;
    return -1;
}

int Automata::find_input(const char &c) {
    if (c == '_') return ULINE_INDX;
    for (int i = 0; i < input_alphabet.size(); ++i)
        if (input_alphabet[i] == c)
            return i;
    return -1;
}

int PDA::set_stack_alphabet(const std::vector<std::string> &s) {
    if (!stack_alphabet.empty())
        return -1;
    for (const auto &s: s)
        stack_alphabet.push_back(s[0]);
    return 0;
}

int PDA::add_stack_alphabet(const char &c) {
    stack_alphabet.push_back(c);
    return 0;
}

int PDA::set_start_symbol(const std::string &s) {
    if (start_symbol != -1)
        return -1;
    start_symbol = find_symbol(s[0]);
    if (start_symbol == -1)
        return -1;
    return 0;
}

int PDA::add_rule(const std::vector<std::string> &s) {
    if (s.size() != 5)
        return -1;
    int state = find_state(s[0]);
    int input = find_input(s[1][0]);
    int symbol = find_symbol(s[2][0]);
    int to_state = find_state(s[3]);
    if (state == -1 || input == -1 || symbol == -1 || to_state == -1)
        return -1;
    std::vector<int> to_symbols;
    for (const auto &c: s[4]) {
        to_symbols.push_back(find_symbol(c));
        if (to_symbols[to_symbols.size() - 1] == -1)
            return -1;
    }
    std::reverse(to_symbols.begin(), to_symbols.end());
    rules.push_back(Rule(state, input, symbol, to_state, to_symbols));
    return 0;
}

void PDA::clear() {
    stack_alphabet.clear();
    start_symbol = -1;
    rules.clear();
}

int PDA::find_symbol(const char &c) {
    if (c == '_') return ULINE_INDX;
    for (int i = 0; i < stack_alphabet.size(); ++i)
        if (stack_alphabet[i] == c)
            return i;
    return -1;
}

char PDA::get_ch(int c) {
    if (c == ULINE_INDX)
        return '_';
    if (c == STAR_INDX)
        return '*';
    return stack_alphabet[c];
}


int TM::set_tape_alphabet(const std::vector<std::string> &s) {
    if (!tape_alphabet.empty())
        return -1;
    for (const auto &s: s)
        if (s[0] != '_')
            tape_alphabet.push_back(s[0]);
    return 0;
}

int TM::add_rule(const std::vector<std::string> &s) {
    if (s.size() != 5)
        return -1;
    // std::cerr << "debug@add_rule" << std::endl;
    int state = find_state(s[0]);
    std::vector<int> symbols = find_symbols(s[1]);
    std::vector<int> to_symbols = find_symbols(s[2]);
    std::string to_dirs = s[3];
    int to_state = find_state(s[4]);
    if (state == -1 || symbols[0] == -1 || to_symbols[0] == -1 || to_state == -1)
        return -1;
    rules.push_back(Rule(state, symbols, to_state, to_symbols, to_dirs));
    return 0;
}

int TM::set_tape_num(const std::string &s) {
    if (tape_num != 0)
        return -1;
    tape_num = std::stoi(s);
    return 0;
}

void TM::clear() {
    tape_alphabet.clear();
    rules.clear();
}

int TM::find_symbol(const char &c) {
    if (c == '_') return ULINE_INDX;
    if (c == '*') return STAR_INDX;
    for (int i = 0; i < tape_alphabet.size(); ++i)
        if (tape_alphabet[i] == c)
            return i;
    return -1;
}

std::vector<int> TM::find_symbols(const std::string &s) {
    std::vector<int> symbols;
    for (const auto &c: s) {
        symbols.push_back(find_symbol(c));
        if (symbols[symbols.size() - 1] == -1) {
            symbols[0] = -1;
            return symbols;
        }
    }
    return symbols;
}

char TM::get_ch(int c) {
    if (c == ULINE_INDX)
        return '_';
    if (c == STAR_INDX)
        return '*';
    return tape_alphabet[c];
}


bool Runner::if_final() {
    // std::cerr << "debug@if_final: " << automata->states[state].name << std::endl;
    return automata->states[state].is_final;
}

int PDA_runner::set_input(const std::string &s) {
    for (int i = 0; i < s.size(); ++i) {
        input.push_back(pda->find_input(s[i]));
        if (input[input.size() - 1] == -1)
            return i;
    }
    stack.push(pda->start_symbol);
    state = pda->start_state;
    steps = 0;
    return -1;
}

bool eq(int input, int rule_input) {
    if (rule_input == ULINE_INDX || rule_input == STAR_INDX)
        return 1;
    if (input == STAR_INDX)
        return 1;
    return input == rule_input;
}

bool eq(const std::stack<int> &stack, int rule_symbol) {
    if (rule_symbol == ULINE_INDX)
        return 1;
    if (stack.empty())
        return 0;
    if (rule_symbol == STAR_INDX)
        return 1;
    if (stack.top() == STAR_INDX)
        return 1;
    return stack.top() == rule_symbol;
}

int PDA_runner::step() {
    // std::cerr << "debug@step: " << pda->states[state].name
    //     << " " << (input_indx == input.size() ? '?' : pda->input_alphabet[input[input_indx]])
    //     << " " << (stack.empty() ? '?' : pda->stack_alphabet[stack.top()]) << std::endl;
    if (input_indx == input.size() && if_final())
        return 2;
    for (const auto &rule: pda->rules) {
        if (state == rule.state && eq(input[input_indx], rule.input) && eq(stack, rule.symbol)) {
            state = rule.to_state;
            if (rule.symbol != ULINE_INDX)
                stack.pop();
            for (const auto &c: rule.to_symbols)
                if (c != ULINE_INDX)
                    stack.push(c);
            if (rule.input != ULINE_INDX)
                ++input_indx;
            return 1;
        }
    }
    return 0;
}

void PDA_runner::print() {
    std::cout << "Step  : " << steps << std::endl;
    std::cout << "State : " << pda->states[state].name << std::endl;
    std::cout << "Stack : ";
    std::stack<int> s2 = stack;
    std::vector<int> v2;
    while (!s2.empty()) {
        v2.push_back(s2.top());
        s2.pop();
    }
    std::reverse(v2.begin(), v2.end());
    for (int j = 0; j < stack.size(); ++j)
        std::cout << pda->get_ch(v2[j]) << " ";
    std::cout << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

int TM_runner::set_input(const std::string &s) {
    heads.assign(tm->tape_num, 0);
    tapes.resize(tm->tape_num);
    for (int i = 0; i < s.size(); ++i) {
        tapes[0].push_back(tm->find_symbol(s[i]));
        if (tapes[0][i] == -1)
            return i;
    }
    for (int i = 1; i < tm->tape_num; ++i)
        tapes[i].push_back(ULINE_INDX);
    state = tm->start_state;
    steps = 0;
    return -1;
}

bool eq(const std::vector<std::vector<int> > &tapes, const std::vector<int> &heads, const std::vector<int> &symbols) {
    for (int i = 0; i < tapes.size(); ++i) {
        if (symbols[i] == STAR_INDX) {
            if (tapes[i][heads[i]] == ULINE_INDX)
                return 0;
        } else if (tapes[i][heads[i]] != symbols[i])
            return 0;
    }
    return 1;
}

int TM_runner::step() {
    // std::cerr << "debug@step: " << tm->states[state].name << " ";
    // for (int i = 0; i < tm->tape_num; ++i) {
    //     int c = tapes[i][heads[i]];
    //     if (c == ULINE_INDX)
    //         std::cerr << '_';
    //     else if (c == STAR_INDX)
    //         std::cerr << '*';
    //     else
    //         std::cerr << tm->tape_alphabet[c];
    // }
    // std::cerr << std::endl;
    ++steps;
    for (const auto &rule: tm->rules) {
        if (state == rule.state && eq(tapes, heads, rule.symbols)) {
            state = rule.to_state;
            for (int i = 0; i < tm->tape_num; ++i) {
                if (rule.to_symbols[i] != STAR_INDX)
                    tapes[i][heads[i]] = rule.to_symbols[i];
                if (rule.to_dirs[i] == 'l')
                    --heads[i];
                if (rule.to_dirs[i] == 'r')
                    ++heads[i];
                while (heads[i] < 0) {
                    tapes[i].insert(tapes[i].begin(), ULINE_INDX);
                    ++heads[i];
                }
                while (heads[i] >= tapes[i].size())
                    tapes[i].push_back(ULINE_INDX);
            }
            return 1;
        }
    }
    return 2;
}

std::string space(int n) {
    std::string s;
    if (n == 0)
        return " ";
    while (n > 0) {
        s.push_back(' ');
        n /= 10;
    }
    return s;
}

void TM_runner::print() {
    std::cout << "Step   : " << steps << std::endl;
    std::cout << "State  : " << tm->states[state].name << std::endl;
    for (int i = 0; i < tm->tape_num; ++i) {
        simp(i, 1);
        std::cout << "Index" << i << " : ";
        for (int j = 0; j < tapes[i].size(); ++j)
            std::cout << j << " ";
        std::cout << std::endl << "Tape" << i << "  : ";
        for (int j = 0; j < tapes[i].size(); ++j)
            std::cout << tm->get_ch(tapes[i][j]) << space(j);
        std::cout << std::endl << "Head" << i << "  : ";
        for (int j = 0; j < tapes[i].size(); ++j)
            if (heads[i] == j)
                std::cout << "^" << space(j);
            else
                std::cout << " " << space(j);
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;
}

std::string TM_runner::output() {
    simp(0, 0);
    std::string s;
    // std::cerr << "debug@output: ";
    // for (const int &c: tapes[0])
    //     std::cerr << c << " ";
    // std::cerr << std::endl;
    for (const auto &c: tapes[0])
        s.push_back(tm->get_ch(c));
    return s;
}

void TM_runner::simp(int i, int t) {
    while (tapes[i].size() > t && tapes[i][0] == ULINE_INDX && heads[i] > 0) {
        tapes[i].erase(tapes[i].begin());
        --heads[i];
    }
    while (tapes[i].size() > t && tapes[i][tapes[i].size() - 1] == ULINE_INDX && heads[i] < tapes[i].size() - 1)
        tapes[i].pop_back();
}
