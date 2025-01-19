#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <fstream>
#include "automata.h"

int read(std::ifstream &file, PDA &p);
int read(std::ifstream &file, TM &t);

#endif //PARSE_H
