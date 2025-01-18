#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <vector>

class State {
public:
    std::string name;
    bool is_final;
};


class Automata {
    std::vector<State> states;
    State &start_state;
    std::vector<char> input_alphabet;

public:
    int set_states(const std::vector<std::string> &s);
    int set_input_alphabet(const std::vector<std::string> &s);
    int set_start_state(const std::string &s);
    int set_final_states(const std::vector<std::string> &s);
};

class PDA : public Automata {
public:
    int set_start_symbol(const std::string &s);
    int add_rule(const std::vector<std::string> &s);
    void clear();
};

class TM : public Automata {

};


#endif //AUTOMATA_H
