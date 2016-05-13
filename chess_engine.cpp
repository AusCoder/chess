#include "chess.h"


/* 
 * temporary functions
 * *****************************************************/

bool can_castle(string input, unordered_map<string, string> *board) {
    return true;
}

bool is_king_safe( const unordered_map<string, string> *board, struct PlayerStatus player_ps) {
    return true;
}

/*******************************************************/

/* 
 * check if user input makes sense 
 */
bool is_valid_input(string input) {
    if (input == "0-0" || input == "0-0-0")
        return true;
    else if (input.length() != 4)
        return false;
    else if (input[0] < 'a' || input[0] > 'h')
        return false;
    else if (input[1] < '1' || input[1] > '8')
        return false;
    else if (input[2] < 'a' || input[2] > 'h')
        return false;
    else if (input[3] < '1' || input[3] > '8')
        return false;
    else
        return true;
}


/* 
 * initialise the board for the beginning of the game 
 */
void init_board( unordered_map<string, string> *board ) {
    string wpos = "a1WRb1WNc1WBd1WQe1WKf1WBg1WNh1WRa2WPb2WPc2WPd2WPe2WPf2WPg2WPh2WP";
    string bpos = "a8BRb8BNc8BBd8BQe8BKf8BBg8BNh8BRa7BPb7BPc7BPd7BPe7BPf7BPg7BPh7BP";

    for(int i = 0; i < 16; i++) {
        string key = wpos.substr(4*i, 2);
        string val = wpos.substr(4*i+2, 2);
        (*board)[key] = val;
    }
    for(int i = 0; i < 16; i++) {
        string key = bpos.substr(4*i, 2);
        string val = bpos.substr(4*i+2, 2);
        //cout << key << " " << val << endl;
        (*board)[key] = val;
    }
    string cols = "abcdefgh";
    string rows = "3456";
    for (unsigned int i = 0; i < cols.size() ; i++) {
        for (unsigned int j = 0; j < rows.size(); j++) {
            string pos = string(1, cols[i]);
            pos += rows[j];
            (*board)[pos] = "-";
        }
    }
}




int main() {

    /* initialise the game board, the player statuses */
    bool white_turn = true; //1 if white's turn; 0 if black's
    unordered_map<string, string> *board = new unordered_map<string, string>();
    struct PlayerStatus white_ps("a4");
    struct PlayerStatus black_ps("h4");
    init_board(board);


    /* initialise the ncurses screen */
    initscr();
    //noecho();
    curs_set(0);

    /* the game loop */
	while(true){
        ncurses_print_board(board, white_turn);

        string input; 
	
	/* loop to get a valid input move */
        while (true) {
            input = get_input();

            if ( input == "q" || input == "quit" || input == "r" || input == "resign")
                break;

            else if (!is_valid_input(input) ) {
                print_error_bad_input(input);
                continue;
            }

            else if (input == "0-0" || input == "0-0-0") { // change to const can_castle
                if (can_castle(input, board))
                    break;
                continue;
            }

            char colour = white_turn? 'W' : 'B';
            char piece = (*board)[input.substr(0,2)][1];
            vector<int> start = to_cart(input.substr(0,2));
            vector<int> end = to_cart(input.substr(2,2));
			for (auto it = end.begin(); it != end.end(); it++)
				cout << *it;
			cout << endl;
            struct PlayerStatus &player_ps = white_turn ? white_ps : black_ps;
            

            if (! is_legal_move(start, end, piece, colour, board) ) {
                // print error
                continue;
            }

            // if player in check, check if proposed move takes out of check
            else if (player_ps.in_check) { 
                string removed_piece = (*board)[input.substr(2,2)];
                update_board(start, end, board);
                if ( is_king_safe(board, player_ps) )
                    break;
                update_board(end, start, board);
                (*board)[input.substr(2,2)] = removed_piece;
                continue;
            }
            // finally we have a legal move
            else {
                // update castle information
                if (piece == 'K') {
                    player_ps.k_pos = input.substr(2,2);
                    player_ps.castle_k_side = false;
                    player_ps.castle_q_side = false;
                }
                if (piece == 'R') {
                    // queen side castle
                    if (start[0] == 1) {
                        player_ps.castle_k_side = false;
                    }
                    // king side castle
                    else if (start[0] == 8) {
                        player_ps.castle_q_side = false;
                    }
                }
                update_board(start, end, board);
                break;
            }
        }

        if (input == "q" || input == "quit")
            break;

		white_turn = !white_turn; /*changes turns*/	
	}

    /* close ncurses */
    endwin();
	// display winner	
    delete board;

	return 0;
}

