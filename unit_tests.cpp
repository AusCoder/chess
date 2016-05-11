#include "chess.h"
bool king_in_check(const unordered_map<string, string> *board, string king_pos);

void cart_test() {
    vector<string> positions {"a1", "h1", "a8", "h8"};
    for (auto it = positions.begin(); it != positions.end(); it++) {
        cout << *it << " " << "( " ;
        vector<int> carts = to_cart(*it);
        for (auto jt = carts.begin(); jt != carts.end(); jt++) {
            cout << *jt << " ";
        }
        cout << ")" << endl;
    }

    vector<int> a1 {1,1};
    vector<int> a8 {1,8};
    vector<int> h1 {8,1};
    vector<int> h8 {8,8};
    cout << "expected: a1" << " "  << to_str(a1[0],a1[1]) << endl;
    cout << "expected: a8" << " "  << to_str(a8[0],a8[1]) << endl;
    cout << "expected: h1" << " "  << to_str(h1[0],h1[1]) << endl;
    cout << "expected: h8" << " "  << to_str(h8[0], h8[1]) << endl;
}

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

void check_test() {
    unordered_map<string, string> *board = new unordered_map<string, string>();
    string cols = "abcdefgh";
    string rows = "12345678";
    for ( int i = 0; i < cols.size(); i++) {
        for (int j = 0; j < rows.size(); j++) {
            string key = string(1, cols[i]);
            key += rows[j];
            (*board)[key] = "-";
        }
    }



    initscr();
    curs_set(0);
    /*
    (*board)["d4"] = "WK";

    for(int x = 1; x<=8; x++) {
        (*board)[to_str(x,8)] = "BQ";
        ncurses_print_board(board, true);
        print_bool(king_in_check(board, "d4"));
        get_input();
        (*board)[to_str(x,8)] = "-";
    }
    for(int y = 1; y<=8; y++) {
        (*board)[to_str(8,y)] = "BR";
        ncurses_print_board(board, true);
        print_bool(king_in_check(board, "d4"));
        get_input();
        (*board)[to_str(8,y)] = "-";
    }
    (*board)["d4"] = "-";
    for(int x = 1; x<=8; x++) {
        (*board)[to_str(x,1)] = "WB";
        ncurses_print_board(board, true);
        print_bool(king_in_check(board, "f4"));
        get_input();
        (*board)[to_str(x,1)] = "-";
    }
    */
    (*board)["f4"] = "BK";
    for(int x = 1; x<=8; x++) {
        (*board)[to_str(x,3)] = "WN";
        ncurses_print_board(board, true);
        print_bool(king_in_check(board, "f4"));
        get_input();
        (*board)[to_str(x,3)] = "-";
    }
    for(int x = 1; x<=8; x++) {
        (*board)[to_str(x,2)] = "WN";
        ncurses_print_board(board, true);
        print_bool(king_in_check(board, "f4"));
        get_input();
        (*board)[to_str(x,2)] = "-";
    }
    for(int x = 1; x<=8; x++) {
        (*board)[to_str(x,5)] = "WN";
        ncurses_print_board(board, true);
        print_bool(king_in_check(board, "f4"));
        get_input();
        (*board)[to_str(x,5)] = "-";
    }
    for(int x = 1; x<=8; x++) {
        (*board)[to_str(5,x)] = "WN";
        ncurses_print_board(board, true);
        print_bool(king_in_check(board, "f4"));
        get_input();
        (*board)[to_str(5,x)] = "-";
    }


    endwin();

    delete board;
}

int main() {

    check_test();

    return 0;
}

