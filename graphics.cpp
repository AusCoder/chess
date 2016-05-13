#include "chess.h"

#define X_OFFSET 10 
#define Y_OFFSET 6
#define X_CELL_SIZE 4
#define Y_CELL_SIZE 1
#define CELL_SPACING 1
#define Y_TURN_SPACING 4
#define BOTTOM_BOARD (Y_OFFSET + 8*Y_CELL_SIZE + 8*CELL_SPACING)
#define Y_TURN_POS (Y_OFFSET + 8*Y_CELL_SIZE + 8*CELL_SPACING + Y_TURN_SPACING)
#define X_TURN_POS 4
#define Y_INPUT_SPACING 4
#define Y_INPUT_POS (Y_OFFSET + 8*Y_CELL_SIZE + 8*CELL_SPACING + Y_TURN_SPACING + Y_INPUT_SPACING)
#define X_INPUT_POS 4
#define Y_ERROR_POS (Y_INPUT_POS - 1)
#define X_ERROR_POS 4




/* print the board to the terminal */
void print_board(const unordered_map<string, string> *board) {
    string cols = "abcdefgh";
    string rows = "12345678";

    for (int j = (int)rows.size()-1 ; j >= 0; j--) {
        for (int i = 0; i < (int)cols.size(); i++) {
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
    const string cols = "abcdefgh";
    const string rows = "12345678";

    /* start by clearing the previous board */
    clear();
    
    /* print the board */
    int x = X_OFFSET, y = Y_OFFSET;
    for (int j = (int)rows.size()-1 ; j >= 0; j--) {
        for (int i = 0; i < (int)cols.size(); i++) {
            string pos = string(1, cols[i]);
            pos += rows[j];
            string val = piece_at(board, to_cart(pos));
            mvprintw(y,x,val.c_str());
            x += X_CELL_SIZE + CELL_SPACING;
        }
        x = X_OFFSET;
        y += Y_CELL_SIZE + CELL_SPACING;
    }

    // print the coordinates
    for (int i = 0; i < (int)cols.size() ; i++) {
        string col = string(1, cols[i]);
        mvprintw( BOTTOM_BOARD, X_OFFSET + i*(X_CELL_SIZE + CELL_SPACING), col.c_str() );
    }
    for (int i = 0; i < (int)cols.size() ; i++) {
        string row = string(1, rows[cols.size()- i-1]);
        mvprintw( Y_OFFSET + i*(Y_CELL_SIZE + CELL_SPACING), X_OFFSET - 4, row.c_str() );
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
    string prompt = "Enter a move: ";
    string overwrite_prompt = prompt + "                                            ";
    mvprintw(Y_INPUT_POS, X_INPUT_POS, overwrite_prompt.c_str());
    move(Y_INPUT_POS, X_INPUT_POS + prompt.length());
    char c;
    string ret = "";
    while ((c = getch()) != '\n') {
        ret += c;
    }
    refresh();
    return ret;
}

/* print bool */
void print_bool(bool x) {
    if (x)
        mvprintw(Y_TURN_POS -2, X_TURN_POS, "King in check: True");
    else
        mvprintw(Y_TURN_POS -2, X_TURN_POS, "King in check: False");
    refresh();
}

/* draw bad input error */
void print_error_bad_input(string input) {
    mvprintw(Y_ERROR_POS, X_ERROR_POS, "Error, bad input:                                 ");
    mvprintw(Y_ERROR_POS, X_ERROR_POS, "Error, bad input: ");
    printw(input.c_str());
    refresh();
}
/* draw bad move error */
void print_error_bad_move(string input) {
    mvprintw(Y_ERROR_POS, X_ERROR_POS, "Error, bad move:                                 ");
    mvprintw(Y_ERROR_POS, X_ERROR_POS, "Error, bad move: ");
    printw(input.c_str());
    refresh();
}
