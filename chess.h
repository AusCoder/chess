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

string piece_at(const unordered_map<string, string> *board, string pos) {
    auto got = board->find(pos);
    if (got == board->end())
        throw "key not found in unordered_map";
    return got->second;
}

#endif
