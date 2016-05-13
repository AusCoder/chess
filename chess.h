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


/* initialise the board */
void init_board( unordered_map<string, string> *board );
/* print board to termial */
void print_board(const unordered_map<string, string> *board);
/* print board with ncurses */
void ncurses_print_board(const unordered_map<string, string> *board, bool);
/* get user input */
string get_input();
void print_bool(bool x);
/* update the game state based on move */
void update_game_state(string move, bool white_turn, unordered_map<string, string> *board,
        struct PlayerStatus *white_ps, struct PlayerStatus *black_ps);
/* convert position string to cartesian coordinates  and vise versa*/
string pair_to_str(int x, int y);
string to_str(vector<int> vec);
vector<int> to_cart(string pos);

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
