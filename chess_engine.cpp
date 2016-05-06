#include "chess.h"


int main() {

    /* initialise the game board, the player statuses */
    bool white_turn = true; //1 if white's turn; 0 if black's
    unordered_map<string, string> *board = new unordered_map<string, string>;
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
        while (true) {
            input = get_input();
            if ( input == "q" || input == "quit" || input == "r" || input == "resign")
                break;
            break;
        }

        if (input == "q" || input == "quit")
            break;
		// interpret user input;
		// redraw GUI;	
        
		// update hashmap;
        //update_game_state("b1a3", board, &white_ps, &black_ps);
		white_turn = !white_turn; /*changes turns*/	
	}

    /* close ncurses */
    endwin();
	// display winner	
    delete board;
	return 0;
}

/* initialise the board for the beginning of the game */
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
    for (int i = 0; i < cols.size() ; i++) {
        for (int j = 0; j < rows.size(); j++) {
            string pos = string(1, cols[i]);
            pos += rows[j];
            (*board)[pos] = "-";
        }
    }
}

/* print the board to the terminal */
void print_board(const unordered_map<string, string> *board) {
    string cols = "abcdefgh";
    string rows = "12345678";

    for (int j = rows.size()-1 ; j >= 0; j--) {
        for (int i = 0; i < cols.size(); i++) {
            string pos = string(1, cols[i]);
            pos += rows[j];
            auto got = board->find(pos);
            if (got == board->end())
                cout << "warning: key not found" << endl;
            else {
                string val = got->second;
                if (val == "-") 
                    cout << " " << val << " ";
                else
                    cout << val << " " ;
            }
        }
        cout << endl;
    }
}

/* print the board using ncurses */
void ncurses_print_board(const unordered_map<string, string> *board, bool white_turn) {
    string cols = "abcdefgh";
    string rows = "12345678";

    /* start by clearing the previous board */
    clear();
    
    /* print the board */
    int x = X_OFFSET, y = Y_OFFSET;
    for (int j = rows.size()-1 ; j >= 0; j--) {
        for (int i = 0; i < cols.size(); i++) {
            string pos = string(1, cols[i]);
            pos += rows[j];
            string val = piece_at(board, pos);
            mvprintw(y,x,val.c_str());
            x += X_CELL_SIZE + CELL_SPACING;
        }
        x = X_OFFSET;
        y += Y_CELL_SIZE + CELL_SPACING;
    }

    /* print who's turn it is */
    if (white_turn)
        mvprintw(Y_TURN_POS,X_TURN_POS, "Turn: White");
    else
        mvprintw(Y_TURN_POS,X_TURN_POS, "Turn: Black");

    refresh();
}

/* print the user prompt */
string get_input() {
    mvprintw(Y_INPUT_POS, X_INPUT_POS, "Enter a move: ");
    char c;
    string ret = "";
    while ((c = getch()) != '\n') {
        ret += c;
    }
    refresh();
    return ret;
}

/* update the current game state with a move */
void update_game_state(string move, unordered_map<string, string> *board,
        struct PlayerStatus *white_ps, struct PlayerStatus *black_ps) {
    if (move.size() != 4) {
        cerr << "warning: move instruction is not 4 characters long!" << endl;
    }
    string start = move.substr(0,2);
    string end = move.substr(2,2);
    //
    // TODO: check if the move puts in check and update the PlayerStatus
    //
    (*board)[end] = (*board)[start];
    (*board)[start] = "-";
}
