#include "chess.h"


int main() {

    bool white_turn = true; //1 if white's turn; 0 if black's
    unordered_map<string, string> *board = new unordered_map<string, string>;

    init_board(board);
    print_board(board);

	while(true){
		// interpret user input;
		// update hashmap;
		// redraw GUI;	

		white_turn = !white_turn; /*changes turns*/	
        break;
	}
	// display winner	
    delete board;
	return 0;
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
