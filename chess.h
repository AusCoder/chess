#ifndef __CHESS_H__
#define __CHESS_H__

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

using namespace std;

// put function declarations here
void init_board( unordered_map<string, string> *board );
void print_board(const unordered_map<string, string> *board);


#endif
