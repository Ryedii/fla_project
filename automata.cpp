#include "automata.h"



void Automata::set_states(std::vector<std::string> &s) {
    states.clear();
    states.resize(s.size());
    for (int i = 0; i < s.size(); ++i)
        states[i].name = s[i];
}

