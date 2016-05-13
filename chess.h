#ifndef __CHESS_H__
#define __CHESS_H__

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <curses.h>
#include <unistd.h>
#include <vector>
#include <cassert>

using namespace std;

// put function declarations here
bool is_legal_move(vector<int> start, vector<int> end,char piece, char colour, unordered_map< string, string > *board);
bool is_king_safe(vector<int> start, vector<int> end, char colour, unordered_map< string, string > *board, struct PlayerStatus player_ps);
bool can_castle(string input, unordered_map< vector<int>, string > *board);
/* IO functions */
void print_board(const unordered_map<string, string> *board);
void ncurses_print_board(const unordered_map<string, string> *board, bool);
string get_input();
void print_error_bad_input(string input);

/* convert position string to cartesian coordinates  and vise versa*/
vector<int> to_cart(string pos);
string to_str(vector<int> vec);
void update_board(vector<int> start, vector<int> end, unordered_map<string, string> *board);
/* get piece at position */
string piece_at(const unordered_map<string, string> *board, vector<int> position);
bool occupied(const unordered_map<string, string> *board, vector<int> position);
/* a king in check function */
//bool king_in_check(const unordered_map<string, string> *board, string king_pos);


struct PlayerStatus {
    bool in_check;
    string k_pos;
    bool castle_k_side;
    bool castle_q_side;

    PlayerStatus(string k_pos) {
        this->in_check = false;
        this->k_pos = k_pos;
        this->castle_k_side = true;
        this->castle_q_side = true;
    }
};

#endif
