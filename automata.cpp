#include "automata.h"

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
    input_alphabet.push_back('_');
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
    for (int i = 0; i < input_alphabet.size(); ++i)
        if (input_alphabet[i] == c)
            return i;
    return -1;
}

int PDA::set_stack_alphabet(const std::vector<std::string> &s) {
    if (!stack_alphabet.empty())
        return -1;
    stack_alphabet.push_back('_');
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
    // add_stack_alphabet(s[0]);
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
    std::cerr << "debug@add_rule " << s[4] << std::endl;
    std::vector<int> to_symbols;
    for (const auto &c: s[4]) {
        to_symbols.push_back(find_symbol(c));
        if (to_symbols[to_symbols.size() - 1] == -1)
            return -1;
    }
    std::cerr << "debug@add_rule" << std::endl;
    rules.push_back(Rule(state, input, symbol, to_state, to_symbols));
    return 0;
}

void PDA::clear() {
    stack_alphabet.clear();
    start_symbol = -1;
    rules.clear();
}

int PDA::find_symbol(const char &c) {
    for (int i = 0; i < stack_alphabet.size(); ++i)
        if (stack_alphabet[i] == c)
            return i;
    return -1;
}

int Runner::if_final() {
    return automata->states[state].is_final;
}

int PDA_runner::set_input(const std::string &s) {
    input = s;
    for (const auto &c: s)
        if (pda->find_input(c) == -1)
            return -1;
    stack.push(pda->start_symbol);
    return 0;
}

int PDA_runner::step() {
    if (input_indx == input.size())
        return 2;
    int input_ = input[input_indx++];
    if (stack.empty())
        return -1;
    int symbol = stack.top();
    for (const auto &rule: pda->rules) {
        if (state == rule.state && input[input_indx] == rule.input && symbol == rule.symbol) {
            state = rule.to_state;
            stack.pop();
            for (const auto &c: rule.to_symbols)
                stack.push(c);
            ++input_indx;
            return 1;
        }
    }
    return 0;
}

void PDA_runner::print() {
}






