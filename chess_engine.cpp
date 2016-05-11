#include "chess.h"


int main() {

    /* initialise the game board, the player statuses */
    bool white_turn = true; //1 if white's turn; 0 if black's
    unordered_map<string, string> *board = new unordered_map<string, string>;
    
    vector<int> k_pos;
    k_pos.push_back(1);
    k_pos.push_back(4);
    struct PlayerStatus white_ps(k_pos);
    
    k_pos.clear();
    k_pos.push_back(8);
    k_pos.push_back(4);
    struct PlayerStatus black_ps(k_pos);
    
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
			
			if (input != "0-0" && input != "0-0-0" && input.length() != 5)
				continue;
			
			char player = white_turn? 'W':'B';
			struct PlayerStatus player_ps = white_turn? white_ps:black_ps;
			
			
			else if (input == "0-0")
				; //routine
				continue;
			else if (input == "0-0-0")
				; //routine
				continue;
			// start, end converted from input...
			
			if (!is_legal_move(start, end, player, board))
				continue;
			
			if (!is_king_safe(board, player_ps.k_pos)) //was player put in check from previous move?
				player_ps.in_check = true;
			
			if (player_ps.in_check)
				unordered_map<vector<int>,string> board2 = unordered_map<vector<int>,string>(*board); //make copy of board
				vector<int> king_position = player_ps.k_pos;
						
				board2[end] = board2[start]; //make proposed move on copied board
				board2[start] = "-";
						
				if (board2[end][1] == 'K')
					player_ps.k_pos = end; //update king's position
					
				if (!is_king_safe(board2, king_position)) 
					player_ps.k_pos = king_position;
					continue; //maybe include error message
				else
					player_ps.in_check = false;
				

			if (board[end][1] == 'K')
				player_ps.k_pos = end; //update king's position
				player_ps.castle_k_side = false;
				player_ps.castle_q_side = false;
			
			else if (board[end][1] == 'R')
				// cases: update player_ps.castle_k_side, player_ps.castle_q_side
			
			board[end] = board[start]; //update board
			board[start] = "-";
			

			white_turn = !white_turn; //changes turn
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

/* initialise the board for the beginning of the game */
void init_board( unordered_map<string, string> *board ) {
    string wpos = "a1WRb1WNc1WBd1WQe1WKf1WBg1WNh1WRa2WPb2WPc2WPd2WPe2WPf2WPg2WPh2WP";
    string bpos = "a8BRb8BNc8BBd8BQe8BKf8BBg8BNh8BRa7BPb7BPc7BPd7BPe7BPf7BPg7BPh7BP";
	int i;
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
