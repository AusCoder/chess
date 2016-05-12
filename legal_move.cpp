#include "chess.h"
																	//ADD en passant routine

bool is_legal_move(vector<int> start, vector<int> end, char colour, unordered_map< vector<int>, string > *board)
{
	char colour = white_turn? 'W': 'B';
	int x1 = start[0], y1= start[1]; // 'start' coordinates
	int x2 = end[0], y2 = end[1]; // 'end' coordinates
	int devX = (x2 - x1 >= 0)? x2-x1: x1-x2; //absolute column deviation
	int devY = (y2 - y1 >= 0)? y2-y1: y1-y2; //absolute row deviation
		
	bool start_in_range = (x1 >= 1) && (x1 <= 8) && (y1 >= 1) && (y1 <= 8); // is valid starting point
	bool end_in_range = (x2 >= 1) && (x2 <= 8) && (y2 >= 1) && (y2 <= 8); // is valid ending point

	if (!(start_in_range && end_in_range)) // position(s) are off the board!
		return false
	
	char piece = piece_at(board, start)[1];
	
	vector<int> intermediate;

	if (piece_at(board, end)[0] != colour){ //ending point is not already occupied by you
	
		if (piece == 'P'){ //PAWN
			if( !occupied(board,end) && y2 == y1 + 1 && devX == 0) //standard jump
				return true;
			else if (y1 == 2 && y2 == 4 && devX == 0) //if first move, double jump allowed
				intermediate.push_back(x1); //intermediate position
				intermediate.push_back(3);
				if (!occupied(board, end) && !occupied(board,intermediate))
					return true;
			else if (occupied(board,end) && y2 == y1 + 1  && devX == 1) //pawn makes a kill
				return true;
		} 
		else if (piece == 'R'){ //ROOK
			int sign;			
			if (devY == 0) //no row deviation; moves along row
				sign = (x2 - x1) > 0? 1: -1;
				int j;
				for(j = 1; j < devX; ++j)
					intermediate.push_back(x1 + sign*j);  //jth intermediate space
					intermediate.push_back(y1);
						if (occupied(board, intermediate))
							return false;
					intermediate.clear();
				return true;
					
			if (devX == 0) //no column deviation; moves along column
				sign = (y2 - y1) > 0? 1: -1;
				int i;
				for(i = 1; i < devY; ++i)
					intermediate.push_back(x1); //jth intermediate space
					intermediate.push_back(y1 + sign*i);
						if (occupied(board, intermediate))
							return false;
					intermediate.clear();
				return true;
			
		}
		else if (piece == 'N'){ //KNIGHT
			if ( (devY == 2 && devX == 1) || (devY == 1 && devX == 2))
				return true;
		}
		else if (piece == 'B'){ //BISHOP
			if (devX == devY) //absolute row deviation = absolute column deviation
				int ySign = (y2 - y1) > 0? 1: -1;
				int xSign = (x2 - x1) > 0? 1: -1;
				int k;
				
				for (k=1; k < devX; ++k){
					intermediate.push_back(x1 + xSign*k); //kth intermediate space
					intermediate.push_back(y1 + ySign*k);
						if (occupied(board,intermediate))
							return false;
					intermediate.clear();
				}
				return true;
		}			
		else if (piece == 'Q'){ //QUEEN
			if (devX == 0 || devY == 0) //behaves like rook, so retest as rook
				return is_legal_move(start, end,'R', colour, *board);
			else if (devX == devY) //behaves like bishop, so retest as bishop
				return is_legal_move(start, end,'B', colour, *board);
		}
		else if (piece == 'K'){ //KING
			if ( devX <= 1 && devY <= 1) //ensures that 'end' is only one move away from 'start'
				return true;
		}
		else if (piece == 'T'){//TONY ABBOTT
			return (start == end); //Tony Abbot is unable to move; he can only cede power.
	}
	return false;	
	}
}






// does the proposed move put player 'colour' in check?
// **will run after is_legal_move, so proposed move will always be legal**
bool is_king_safe(unordered_map< vector<int>, string > *board, vector<int> king_pos) 
{
	char opponent = white_turn?'B':'W';

	int king_x = king_pos[0], king_y = king_pos[1];
	int i;
	string piece;
	vector<int> position;
	
	//determine if enemy rook (or queen) is in striking distance
	for(i=0; i < 8; ++i){
		position.push_back(i);
		position.push_back(king_y);
		if (!((board -> find(position)) == (board -> end()))) {
			piece = piece_at(board,position);
			if( (piece[0] == opponent) && ( piece[1] == 'R' || piece[1] == 'Q')){ //if piece is an enemy rook or queen
				if (is_legal_move(position, king_pos, piece[1], piece[0], board)) //if piece can reach king
					return false;
			}
		}
		position.clear();
	}
	for(i=0; i < 8; ++i){
		position.push_back(king_x);
		position.push_back(i);
		if (!((board -> find(position)) == (board -> end()))) {
			piece = piece_at(board,position);	
			if( (piece[0] == opponent) && ( piece[1] == 'R' || piece[1] == 'Q')){ //if piece is an enemy rook or queen
				if (is_legal_move(position, king_pos, piece[1], piece[0], board)) //if piece can reach king
					return false;
			}
		}
		position.clear();
	}
	
	//determine if enemy bishop (or queen) is in striking distance
	for(i=-4; i < 5; ++i){
		position.push_back(king_x + i);
		position.push_back(king_y + i);
		if (!((board -> find(position)) == (board -> end()) && i!=0)){ //if position is on board (and not where king is)
			piece = piece_at(board,position);
			if( (piece[0] == opponent) && ( piece[1] == 'B' || piece[1] == 'Q')){ //if piece is an enemy bishop or queen
				if (is_legal_move(position, king_pos, piece[1], piece[0], board)) //if piece can reach king
					return false;
			}
		}
		position.clear();
	}
	for(i=-4; i < 5; ++i){
		position = {king_x + i, king_y - i};
		if (!((board -> find(position)) == (board -> end()) &&  i!=0 )) { //if position is on board (and not where the king is)
			piece = piece_at(board,position);
			if( (piece[0] == opponent) && ( piece[1] == 'B' || piece[1] == 'Q')){ //if piece is an enemy bishop or queen
				if (is_legal_move(position, king_pos, piece[1], piece[0], board)) //if piece can reach king
					return false;
			}
		}
		position.clear();
	}		
	
	vector<int> positions;
	
	//determine if enemy knight is in striking distance
	vector<int> N_positions
	positions.push_back(king_x - 2);
	positions.push_back(king_y - 1);
	positions.push_back(king_x - 2);
	positions.push_back(king_y + 1);
	positions.push_back(king_x + 2);
	positions.push_back(king_y - 1);
	positions.push_back(king_x + 2);
	positions.push_back(king_y + 1);
	positions.push_back(king_x - 1);
	positions.push_back(king_y - 2);
	positions.push_back(king_x - 1);
	positions.push_back(king_y + 2);
	positions.push_back(king_x + 1);
	positions.push_back(king_y - 2);
	positions.push_back(king_x + 1);
	positions.push_back(king_y + 2);

	for (i = 0; i < 16; i = i+2){
			position.push_back(positions[i]);
			position.push_back(positions[i+1]);
			if (!((board -> find(position)) == (board -> end()) )) {
				piece = piece_at(board,position);
				if ((piece[0] == opponent) && (piece[1] == 'N'))
					return false;
			}
			position.clear();
	}
	positions.clear();

	
	//determine if enemy pawn is in striking distance
	int sign = white_turn? 1 : -1 ;
	positions.push_back(king_x - 1);
	positions.push_back(king_y + sign);
	positions.push_back(king_x + 1);
	positions.push_back(king_y + sign);

	for (i=0; i < 4; i=i+2){
		position.push_back(positions[i]);
		position.push_back(positions[i+1]);
		if (!((board -> find(position)) == (board -> end()))) {
			piece = piece_at(board,position);
			if ((piece[0] == opponent) && (piece[1] == 'P'))
				return false;
		}
		position.clear();
	}
	positions.clear();
	

	//determine if enemy king is in striking distance
	vector<int> K_positions {king_x-1,king_y-1,king_x,king_y-1,king_x+1,
		king_y-1,king_x-1,king_y,king_x+1,king_y,king_x-1,king_y+1,king_x,
		king_y+1,king_x+1,king_y+1};

	for (i = 0; i < 16; i = i + 2){
		position.push_back(K_positions[i]);
		position.push_back(K_positions[i+1]);
		if (!((board -> find(position)) == (board -> end()) )) {
			piece = piece_at(board,position);
			if ((piece[0] == opponent) && (piece[1] == 'K'))
				return false;
		}
		position.clear();
	}
	
	return true;
}









bool can_castle(string input, unordered_map< vector<int>, string > *board)
//if can successfully castle, updates board and returns true; returns false otherwise
{
	struct PlayerStatus player_ps = white_turn? white_ps: black_ps
	int row = white_turn? 1:8;
	vector<int> king_start {5,row};
			
	if (input == "0-0"){ //king-side castling
		if (!player_ps.castle_k_side)
			return false;
		vector<int> rook_start {8,row};
		vector<int> rook_end {6,row};
		vector<int> king_end {7,row};
	}
	
	else if (input == "0-0-0"){ //queen-side castling
		vector<int> queen_spot {4, row}; 
		if (!player_ps.castle_q_side || occupied(board, queen_spot))
			return false;
		
		vector<int> rook_start {1,row};
		vector<int> rook_end {4,row};
		vector<int> king_end {3,row};
					
	if (!occupied(board,king_end) && !occupied(board,rook_end)){
		unordered_map<vector<int>,string> board2 = unordered_map<string,string>(*board); //make copy of board
		update_board(rook_start, rook_end, board2);
		update_board(king_start, king_end, board2);
		
		if (is_king_safe(board2, king_end)){
			update_board(rook_start, rook_end, board);
			update_board(king_start, king_end, board);
			
			player_ps.k_pos = king_end;
			player_ps.castle_k_side = false;
			player_ps.castle_q_side = false;
			return true;
		} 		
	}
	return false;
}





