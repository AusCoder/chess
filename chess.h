#ifndef __CHESS_H__
#define __CHESS_H__

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <curses.h>
#include <unistd.h>
#include <vector>

using namespace std;

// put function declarations here
bool is_legal_move(string start, string end, char piece, char colour, unordered_map< string, string > *board);
bool is_king_safe(string start, string end, char colour, unordered_map< string, string > *board);
bool can_castle(char colour, int i, bool castle_unmoved, unordered_map< string, string > *board);

/* initialise the board */
void init_board( unordered_map<string, string> *board );
/* print board to termial */
void print_board(const unordered_map<string, string> *board);
/* print board with ncurses */
void ncurses_print_board(const unordered_map<string, string> *board, bool);
/* get user input */
string get_input();
/* update the game state based on move */
void update_game_state(string move, unordered_map<string, string> *board,
        struct PlayerStatus *white_ps, struct PlayerStatus *black_ps);
/* convert position string to cartesian coordinates */
vector<int> to_cart(string pos);
/* get piece at position */
string piece_at(const unordered_map<string, string> *board, string pos);


inline bool occupied(const unordered_map<string, string> *board, string pos){
	return (piece_at(board,pos) != "-");
}

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
