#ifndef __CHESS_H__
#define __CHESS_H__

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <curses.h>
#include <unistd.h>

#define X_OFFSET 4
#define Y_OFFSET 2
#define X_CELL_SIZE 4
#define Y_CELL_SIZE 1
#define CELL_SPACING 1
#define Y_TURN_SPACING 2
#define Y_TURN_POS (Y_OFFSET + 8*Y_CELL_SIZE + 8*CELL_SPACING + Y_TURN_SPACING)
#define X_TURN_POS 4
#define Y_INPUT_SPACING 4
#define Y_INPUT_POS (Y_OFFSET + 8*Y_CELL_SIZE + 8*CELL_SPACING + Y_TURN_SPACING + Y_INPUT_SPACING)
#define X_INPUT_POS 4


using namespace std;

// put function declarations here
bool legal_move(string start, string end, char piece, char colour, unordered_map< string, string > *board);

void init_board( unordered_map<string, string> *board );
void print_board(const unordered_map<string, string> *board);
void ncurses_print_board(const unordered_map<string, string> *board, bool);
string get_input();


string piece_at(const unordered_map<string, string> *board, string pos) {
    auto got = board->find(pos);
    if (got == board->end())
        throw "key not found in unordered_map";
    return got->second;
}

bool occupied(const unordered_map<string, string> *board, string pos){
	return (piece_at(board,pos) != "-");
}

#endif
