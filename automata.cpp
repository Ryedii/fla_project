#include "automata.h"

#include <cstring>


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


int PDA::set_stack_alphabet(const std::vector<char> &s) {
    if (!stack_alphabet.empty())
        return -1;
    stack_alphabet.push_back('_');
    for (const auto &s: s)
        stack_alphabet.push_back(s[0]);
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
    int state_indx = find_state(s[0]);
    int input_indx = find_input(s[1][0]);
    int symbol_indx = find_symbol(s[2][0]);
    int to_state_indx = find_state(s[3]);
    if (state_indx == -1 || input_indx == -1 || symbol_indx == -1 || to_state_indx == -1)
        return -1;
    std::vector<int> to_symbols_indx;
    for (const auto &c: s[4]) {
        to_symbols_indx.push_back(find_symbol(c));
        if (to_symbols_indx[to_symbols_indx.size() - 1] == -1)
            return -1;
    }
#define indx state_indx][input_indx][symbol_indx
    to_state[indx] = to_state_indx;
    to_symbols[indx] = to_symbols_indx;
}


void PDA::clear() {
    stack_alphabet.clear();
    start_symbol = -1;
    memset(to_state, -1, sizeof(to_state));
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
    int state_indx = state;
    int input_indx = input[input_indx];
    if (stack.empty())
        return -1;
    int symbol_indx = stack.top();
#define indx state_indx][input_indx][symbol_indx
    int to_state_indx = pda->to_state[indx];
    if (to_state_indx == -1)
        return 0;
    state = to_state_indx;
    stack.pop();
    for (const auto &c: pda->to_symbols[indx])
        stack.push(c);
    ++input_indx;
    return 1;
}

void PDA_runner::print() {

}

void PDA_runner::if_final() {
    return pda.stat
}





