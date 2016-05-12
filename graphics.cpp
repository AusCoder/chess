#include "chess.h"

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
            string val = piece_at(board, to_cart(pos));
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

/* print bool */
void print_bool(bool x) {
    if (x)
        mvprintw(Y_TURN_POS -2, X_TURN_POS, "King in check: True");
    else
        mvprintw(Y_TURN_POS -2, X_TURN_POS, "King in check: False");
    refresh();
}
