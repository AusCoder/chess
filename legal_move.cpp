#include <cmath>
#include "chess.h"
																	//ADD en passant routine

bool is_legal_move(vector<int> start, vector<int> end, const unordered_map< string, string > *board)
{
	int x1 = start[0], y1= start[1]; // 'start' coordinates
	int x2 = end[0], y2 = end[1]; // 'end' coordinates
	int devX = (x2 - x1 >= 0)? x2-x1: x1-x2; //absolute column deviation
	int devY = (y2 - y1 >= 0)? y2-y1: y1-y2; //absolute row deviation
		
	bool start_in_range = (x1 >= 1) && (x1 <= 8) && (y1 >= 1) && (y1 <= 8); // is valid starting point
	bool end_in_range = (x2 >= 1) && (x2 <= 8) && (y2 >= 1) && (y2 <= 8); // is valid ending point

	if (!(start_in_range && end_in_range)) // position(s) are off the board!
		return false;
	
	char colour = piece_at(board, start)[0];
	char piece = piece_at(board, start)[1];
	vector<int> intermediate;

	if (piece_at(board, end)[0] != colour){ //ending point is not already occupied by you
	
		if (piece == 'P'){ //PAWN
			int sign = (colour == 'W')? 1: -1;
			if( !occupied(board,end) && y2 == y1 + sign && devX == 0){ //standard jump
				return true;
			}
			else if (colour == 'W' && y1 == 2 && y2 == 4 && devX == 0){ //if white's first move, double jump allowed
				vector<int> intermediate {x1,3}; //intermediate position
				if (!occupied(board, end) && !occupied(board,intermediate))
					return true;
			}
			else if (colour == 'B' && y1 == 7 && y2 == 5 && devX == 0){ //if black's first move, double jump allowed
				vector<int> intermediate {x1,6}; //intermediate position
				if (!occupied(board, end) && !occupied(board,intermediate))
					return true;
			}
			else if (occupied(board,end) && y2 == y1 + sign  && devX == 1) //pawn makes a kill
				return true;
		}
		 
		else if (piece == 'R' || piece == 'Q'){ //ROOK/QUEEN
			int sign;			
			if (devY == 0) //no row deviation; moves along row
				sign = (x2 - x1) > 0? 1: -1;
				int j;
				for(j = 1; j < devX; ++j)
					vector<int> intermediate {x1 + sign*j, y1};  //jth intermediate space
					if (occupied(board, intermediate))
						return false;
				return true;
					
			if (devX == 0) //no column deviation; moves along column
				sign = (y2 - y1) > 0? 1: -1;
				int i;
				for(i = 1; i < devY; ++i)
					vector<int> intermediate {x1,y1 + sign*i}; //jth intermediate space
					if (occupied(board, intermediate))
						return false;
				return true;
			
		}
		else if (piece == 'N'){ //KNIGHT
			if ( (devY == 2 && devX == 1) || (devY == 1 && devX == 2))
				return true;
		}
		else if (piece == 'B' || piece == 'Q'){ //BISHOP/QUEEN
			if (devX == devY) {//absolute row deviation = absolute column deviation
				int y_sign = (y2 - y1) > 0? 1: -1;
				int x_sign = (x2 - x1) > 0? 1: -1;
				int k;
				
				for (k=1; k < devX; ++k){
					vector<int> intermediate {x1 + (x_sign)*k,y1 + (y_sign)*k}; //kth intermediate space
					if (occupied(board,intermediate))
						return false;
				}
				return true;
			}
		}			
		
		else if (piece == 'K'){ //KING
			if ( devX <= 1 && devY <= 1) //ensures that 'end' is only one move away from 'start'
				return true;
		}
		return false;
	}
	else
		return false;
}






// does the proposed move put player 'colour' in check?
// **will run after is_legal_move, so proposed move will always be legal**
bool is_king_safe(const unordered_map< string, string > *board, struct PlayerStatus player_ps) 
{
	vector<int> king_pos = to_cart(player_ps.k_pos);
	char player = (piece_at(board, king_pos)[0] == 'W')?'W':'B';
	char opponent = (player == 'W')? 'B': 'W';
	
	int king_x = king_pos[0], king_y = king_pos[1];
	int i;
	string piece;
		
	
	//determine if enemy rook (or queen) is in striking distance
	
	for(i=1; i < 8; ++i){ //searching right
		vector<int> position {king_x + i, king_y};
		if (!((board -> find(to_str(position))) == (board -> end()))) {
			piece = piece_at(board, position);
			if( (piece[0] == opponent) && ( piece[1] == 'R' || piece[1] == 'Q')){ //if piece is an enemy rook or queen
				return false;
			}
		else
			i = 8;
		}
	}
	
	for(i=1; i < 8; ++i){ //searching left
		vector<int> position {king_x - i, king_y};
		if (!((board -> find(to_str(position))) == (board -> end()))) {
			piece = piece_at(board, position);
			if( (piece[0] == opponent) && ( piece[1] == 'R' || piece[1] == 'Q')){ //if piece is an enemy rook or queen
				return false;
			}
		else
			i = 8;
		}
	}
	
	for(i=1; i < 8; ++i){ //searching up
		vector<int> position {king_x, king_y + i};
		if (!((board -> find(to_str(position))) == (board -> end()))) {
			piece = piece_at(board, position);
			if( (piece[0] == opponent) && ( piece[1] == 'R' || piece[1] == 'Q')){ //if piece is an enemy rook or queen
				return false;
			}
		else
			i = 8;
		}
	}
	for(i=1; i < 8; ++i){ //searching down
		vector<int> position {king_x, king_y - i};
		if (!((board -> find(to_str(position))) == (board -> end()))) {
			piece = piece_at(board, position);
			if( (piece[0] == opponent) && ( piece[1] == 'R' || piece[1] == 'Q')){ //if piece is an enemy rook or queen
				return false;
			}
		else
			i = 8;
		}
	}
	
	//determine if enemy bishop (or queen) is in striking distance
	for(i= 1; i < 8; ++i){ //searching right-up direction
		vector<int> position {king_x + i, king_y + i};
		if (!((board -> find(to_str(position))) == (board -> end()))){ 
			piece = piece_at(board,position);
			if( (piece[0] == opponent) && ( piece[1] == 'B' || piece[1] == 'Q')){ //if piece is an enemy bishop or queen
				return false;
			}
		else
			i = 8;
		}
	}
	
	for(i= 1; i < 8; ++i){ //searching right-down direction
		vector<int> position {king_x + i, king_y - i};
		if (!((board -> find(to_str(position))) == (board -> end()))){ 
			piece = piece_at(board,position);
			if( (piece[0] == opponent) && ( piece[1] == 'B' || piece[1] == 'Q')){ //if piece is an enemy bishop or queen
				return false;
			}
		else
			i = 8;
		}
	}
	
	for(i= 1; i < 8; ++i){ //searching left-up direction
		vector<int> position {king_x - i, king_y + i};
		if (!((board -> find(to_str(position))) == (board -> end()))){ 
			piece = piece_at(board,position);
			if( (piece[0] == opponent) && ( piece[1] == 'B' || piece[1] == 'Q')){ //if piece is an enemy bishop or queen
				return false;
			}
		else
			i = 8;
		}
	}
	
	for(i= 1; i < 8; ++i){ //searching left-down direction
		vector<int> position {king_x - i, king_y - i};
		if (!((board -> find(to_str(position))) == (board -> end()))){ //if position is on board (and not where king is)
			piece = piece_at(board,position);
			if( (piece[0] == opponent) && ( piece[1] == 'B' || piece[1] == 'Q')){ //if piece is an enemy bishop or queen
				return false;
			}
		else
			i = 8;
		}
	}
	
	
	//determine if enemy knight is in striking distance
	vector<int> N_positions {king_x - 2,king_y - 1,king_x - 2,
		king_y + 1, king_x + 2, king_y - 1, king_x + 2, king_y + 1,
		king_x - 1, king_y - 2, king_x - 1, king_y + 2, king_x + 1,
		king_y - 2, king_x + 1, king_y + 2};

	for (i = 0; i < 16; i = i+2){
			vector<int> position {N_positions[i], N_positions[i+1]};
			if (!((board -> find(to_str(position))) == (board -> end()) )) {
				piece = piece_at(board,position);
				if ((piece[0] == opponent) && (piece[1] == 'N'))
					return false;
			}
	}
	
	//determine if enemy pawn is in striking distance
	int sign = (player == 'W')? 1 : -1 ;
	vector<int> P_positions {king_x - 1, king_y + sign, king_x + 1, king_y + sign};

	for (i=0; i < 4; i=i+2){
		vector<int> position {P_positions[i], P_positions[i+1]};
		if (!((board -> find(to_str(position))) == (board -> end()))) {
			piece = piece_at(board,position);
			if ((piece[0] == opponent) && (piece[1] == 'P'))
				return false;
		}
	}	

	//determine if enemy king is in striking distance
	vector<int> K_positions {king_x-1,king_y-1,king_x,king_y-1,king_x+1,
		king_y-1,king_x-1,king_y,king_x+1,king_y,king_x-1,king_y+1,king_x,
		king_y+1,king_x+1,king_y+1};

	for (i = 0; i < 16; i = i + 2){
		vector<int> position {K_positions[i], K_positions[i+1]};
		if (!((board -> find(to_str(position))) == (board -> end()) )) {
			piece = piece_at(board,position);
			if ((piece[0] == opponent) && (piece[1] == 'K'))
				return false;
		}
	}
	
	return true;
}

bool can_castle(string input, unordered_map< string, string > *board, struct PlayerStatus &player_ps)
//if can successfully castle, updates board and returns true; returns false otherwise
{
	char player = piece_at(board, to_cart(player_ps.k_pos))[0];
	int row = (player == 'W')? 1:8;
	vector<int> king_start {5,row};
	vector<int> rook_start, rook_end, king_end;		
	if (input == "0-0"){ //king-side castling
		if (!player_ps.castle_k_side)
			return false;
		vector<int> rook_start {8,row};
		vector<int> rook_end {6,row};
		vector<int> king_end {7,row};
	}
	
	else{ //queen-side castling
		vector<int> queen_spot {4, row}; 
		if (!player_ps.castle_q_side || occupied(board, queen_spot))
			return false;
		
		vector<int> rook_start {1,row};
		vector<int> rook_end {4,row};
		vector<int> king_end {3,row};
	}
					
	if (!occupied(board,king_end) && !occupied(board,rook_end)){
		unordered_map<string,string> board2 = unordered_map<string,string>(*board); //make copy of board
		update_board(rook_start, rook_end, &board2);
		update_board(king_start, king_end, &board2);
		
		if (is_king_safe(&board2, player_ps)){
			update_board(rook_start, rook_end, board);
			update_board(king_start, king_end, board);
			
			player_ps.k_pos = to_str(king_end);
			player_ps.castle_k_side = false;
			player_ps.castle_q_side = false;
			return true;
		} 		
	}
	return false;

}












