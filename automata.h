#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <stack>
#include <string>
#include <vector>
#include <map>

const int ULINE_INDX = 257;
const int STAR_INDX = 258;

class State;
class Automata;
class PDA;
class TM;
class Runner;
class PDA_runner;
class TM_runner;

class State {
public:
    std::string name;
    bool is_final;

    State(const std::string &name) : name(name), is_final(false) {}
};

class Automata {
protected:
    std::vector<State> states;
    int start_state;
    std::vector<char> input_alphabet;

public:
    Automata() { clear(); }
    int set_states(const std::vector<std::string> &s);
    int set_input_alphabet(const std::vector<std::string> &s);
    int set_start_state(const std::string &s);
    int set_final_states(const std::vector<std::string> &s);
    void clear();
    int find_state(const std::string &s);
    int find_input(const char &c);
    friend class Runner;
};

class PDA : public Automata {
private:
    std::vector<char> stack_alphabet;
    int start_symbol;

    struct Rule {
        int state, input, symbol;
        int to_state;
        std::vector<int> to_symbols;

        Rule(int state, int input, int symbol, int to_state, std::vector<int> &to_symbols)
            : state(state), input(input), symbol(symbol), to_state(to_state), to_symbols(std::move(to_symbols)) {}
    };

    std::vector<Rule> rules;

public:
    PDA() { clear(); }
    int set_stack_alphabet(const std::vector<std::string> &s);
    int add_stack_alphabet(const char &c);
    int set_start_symbol(const std::string &s);
    int add_rule(const std::vector<std::string> &s);
    void clear();
    int find_symbol(const char &c);
    friend class PDA_runner;
};

class TM : public Automata {
private:
    std::vector<char> tape_alphabet;
    int tape_num;

    struct Rule {
        int state;
        std::vector<int> symbols;
        int to_state;
        std::vector<int> to_symbols;
        std::string to_dirs;

        Rule(int state, std::vector<int> &symbols, int to_state, std::vector<int> &to_symbols, std::string &to_dirs)
            : state(state), symbols(std::move(symbols)), to_state(to_state), to_symbols(std::move(to_symbols)),
              to_dirs(std::move(to_dirs)) {}
    };

    std::vector<Rule> rules;

public:
    TM() { clear(); }
    int set_tape_alphabet(const std::vector<std::string> &s);
    int add_rule(const std::vector<std::string> &s);
    int set_tape_num(const std::string &s);
    void clear();
    int find_symbol(const char &c);
    std::vector<int> find_symbols(const std::string &s);
    friend class TM_runner;
};

class Runner {
protected:
    Automata *automata;
    std::vector<int> input;
    int input_indx;
    int state;

public:
    Runner() : input_indx(0), state(-1) {}

    bool if_final();
};

class PDA_runner : public Runner {
private:
    PDA *pda;
    std::stack<int> stack;

public:
    PDA_runner(PDA *pda) : pda(pda) {
        automata = pda;
    }

    int set_input(const std::string &s);
    int step();
    void print();
};

class TM_runner : public Runner {
private:
    TM *tm;
    std::vector<int> heads;
    std::vector<std::vector<int> > tapes;

public:
    TM_runner(TM *tm) : tm(tm) {
        automata = tm;
    }

    int set_input(const std::string &s);
    int step();
    void print();
    std::string output();
};


#endif //AUTOMATA_H
