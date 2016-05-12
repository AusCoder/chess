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
			char player = white_turn? 'W':'B';
			struct PlayerStatus player_ps = white_turn? white_ps: black_ps;
						
			if ( input == "q" || input == "quit" || input == "r" || input == "resign")
				break;
			
			else if (input != "0-0" && input != "0-0-0" && input.length() != 5){
				//output error message?
				continue;
			}			
						
			else if (input == "0-0" || input == "0-0-0"){
				int i = (input == "0-0")? 1 : 2; 
				int castle_success = can_castle(i, board);
				
				if (castle_success == 0) //if castling failed
					continue; //output error message?
				}
			
			
			else {
				int x1 = input[0] - 'a' + 1;
				int y1 = input[1] - '1' + 1;
				int x2 = input[2] - 'a' + 1;
				int y2 = input[3] - '1' + 1;
				vector<int> start {x1,y1};
				vector<int> end {x2,y2};
								
				if (!is_legal_move(start, end, player, board))
					//output error message?
					continue;
				
				if (player_ps.in_check){
					unordered_map<vector<int>,string> board2 = unordered_map<vector<int>,string>(*board); //make copy of board
					vector<int> king_position = player_ps.k_pos;
							
					board2[end] = board2[start]; //make proposed move on copied board
					board2[start] = "-";
							
					if (board2[end][1] == 'K')
						player_ps.k_pos = end; //update king's position
						
					if (!is_king_safe(board2, king_position)){ 
						player_ps.k_pos = king_position;
						continue; //maybe include error message
					}
					else
						player_ps.in_check = false;
				}
					

				if (board[start][1] == 'K'){
					player_ps.k_pos = end; //update king's position
					player_ps.castle_k_side = false;
					player_ps.castle_q_side = false;
				}
				
				else if (board[start][1] == 'R'){
					vector<int> k_rook_start, q_rook_start;
					int row = white_turn? 1:8;
					k_rook_start.push_back(1);
					k_rook_start.push_back(row);
					q_rook_start.push_back(8);
					q_rook_start.push_back(row);
					
					if (start == k_rook_start)
						player_ps.castle_k_side = false;
					else if (start == q_rook_start)
						player_ps.castle_k_side = false;
				}
				
				board[end] = board[start]; //update board
				board[start] = "-";
			}

			white_turn = !white_turn; //changes turn
			
			struct PlayerStatus opponent_ps = white_turn? black_ps: white_ps;
			
			if (!is_king_safe(board, opponent_ps.k_pos)) //was opponent put in check?
				opponent_ps.in_check = true;
	}


        if (input == "q" || input == "quit")
            break;
		
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
