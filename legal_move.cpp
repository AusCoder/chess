#include <cmath>
#include "chess.h"
																	//ADD en passant routine
/*.....................................................................................
bool is_legal_move(vector<int> start, vector<int> end, char piece, char colour, unsorted_map< string, string > *board)
{
	int x1 = start[0], y1= start[1]; // 'start' coordinates
	int x2 = end[0], y2 = end[1]; // 'end' coordinates
	int devX = (x2 - x1 >= 0)? x2-x1: x1-x2; //absolute column deviation
	int devX = (y2 - y1 >= 0)? y2-y1: y1-y2; //absolute row deviation
		
	bool start_in_range = (x1 >= 1) && (x1 <= 8) && (y1 >= 1) && (y1 <= 8); // is valid starting point
	bool end_in_range = (x2 >= 1) && (x2 <= 8) && (y2 >= 1) && (y2 <= 8); // is valid ending point

	if (!(start_in_range && end_in_range)) // position(s) are off the board!
		return false
	
	vector<int> intermediate;

	if (piece_at(board, end)[0] != colour){ //ending point is not already occupied by you
	
		if (piece == 'P'){ //PAWN
			if( !occupied(board,end) && y2 == y1 + 1 && devX == 0) //standard jump
				return true;
			else if (y1 == 2 && y2 == 4 && devX == 0) //if first move, double jump allowed
				intermediate ==  {x1, 3}; //intermediate position
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
					intermediate = {x1 + sign*j, y1}; //jth intermediate space
						if (occupied(board, intermediate))
							return false;
				return true;
					
			if (devX == 0) //no column deviation; moves along column
				sign = (y2 - y1) > 0? 1: -1;
				int i;
				for(i = 1; i < devY; ++i)
					intermediate = {x1, y1 + sign*i}; //jth intermediate space
						if (occupied(board, intermediate))
							return false;
				return true;
			
		}
		else if (piece == 'N'){ //KNIGHT
			if ( (devY == 2 && devX == 1) || (devY == 1 && devX == 2))
				return true;
		}
		
		else if (piece == 'B'){ //BISHOP
			if (devR == devC) //absolute row deviation = absolute column deviation
				int ySign = (y2 - y1) > 0? 1: -1;
				int xSign = (x2 - x1) > 0? 1: -1;
				int k;
				
				for (k=1; k < devX; ++k);
					intermediate = {x1 + xSign*k, y1 + ySign*k}; // kth intermediate space
		}				if (occupied(board,intermediate))
							return false;
				return true;
			
		else if (piece == 'Q'){ //QUEEN
			if (devX == 0 || devY == 0) //behaves like rook, so retest as rook
				return is_legal_move(start, end,'R', colour, *board);
			else if (devR == devC) //behaves like bishop, so retest as bishop
				return is_legal_move(start, end,'B', colour, *board);
		}
		else if (piece == 'K'){ //KING
			if ( devR <= 1 && devC <= 1) //ensures that 'end' is only one move away from 'start'
				return true;
		}
		else if (piece == 'T'){//TONY ABBOTT
			return (start == end); //Tony Abbot is unable to move; he can only cede power.
	}
	return false;	
}




.....................................................................................*/

// does the proposed move put player 'colour' in check?
// **will run after is_legal_move, so proposed move will always be legal**
/*
bool is_king_safe(vector<int> start, vector<int> end, char colour, unsorted_map< string, string > *board, struct PlayerStatus player_ps) 
{
	string king_pos = player_ps.k_pos; //king's position
	char opponent = (colour=='W')? 'B':'W';
    
	if (piece_at(board, start) == string(1,colour) + string(1,'K')) //if king is to be moved, update king's position
		king_pos = end; 

	unordered_map<string,string> board2 = unordered_map<string,string>(*board); //make copy of board
	board2[end] = board2[start]; //make proposed move on copied board
	board2[start] = "-";

	int king_x = king_pos[0], king_y = king_pos[1];
	int i;
	string piece;
	vector<int> position;
	
	//determine if enemy rook (or queen) is in striking distance
	for(i=0; i < 8; ++i){
		position = {i, king_y};
		piece = piece_at(board2,position);
		if( (piece[0] == opponent) && ( piece[1] == 'R' || piece[1] == 'Q')){ //if piece is an enemy rook or queen
			if (is_legal_move(position, king_pos, piece[1], piece[0], board2)) //if piece can reach king
				return false;
		}
	}
	for(i=0; i < 8; ++i){
		position = {king_x, i};
		piece = piece_at(board2,position);
		if( (piece[0] == opponent) && ( piece[1] == 'R' || piece[1] == 'Q')){ //if piece is an enemy rook or queen
			if (is_legal_move(position, king_pos, piece[1], piece[0], board2)) //if piece can reach king
				return false;
		}
	}
	
	//determine if enemy bishop (or queen) is in striking distance
	for(i=-4; i < 5; ++i){
		position = {king_x + i, king_y + i};
		if (!((board -> find(position)) == (board -> end()) && i!=0)) //if position is on board (and not where king is)
			piece = piece_at(board2,position);
			if( (piece[0] == opponent) && ( piece[1] == 'B' || piece[1] == 'Q')){ //if piece is an enemy bishop or queen
				if (is_legal_move(position, king_pos, piece[1], piece[0], board2)) //if piece can reach king
					return false;
		}
	}
	for(i=-4; i < 5; ++i){
		position = {king_x + i, king_y - i};
		if (!((board -> find(position)) == (board -> end()) &&  i!=0 )) //if position is on board (and not where the king is)
			piece = piece_at(board2,position);
			if( (piece[0] == opponent) && ( piece[1] == 'B' || piece[1] == 'Q')){ //if piece is an enemy bishop or queen
				if (is_legal_move(position, king_pos, piece[1], piece[0], board2)) //if piece can reach king
					return false;
		}
	}		
	
	vector<vector<int>> positions; //a vector of possible positions

	//determine if enemy knight is in striking distance
	positions.push_back({king_x - 2, king_y - 1});
	positions.push_back({king_x - 2, king_y + 1});
	positions.push_back({king_x + 2, king_y - 1});
	positions.push_back({king_x + 2, king_y + 1});
	positions.push_back({king_x - 1, king_y - 2});
	positions.push_back({king_x - 1, king_y + 2});
	positions.push_back({king_x + 1, king_y - 2});
	positions.push_back({king_x + 1, king_y + 2});

	for (i = 0; i < 8; ++i)
			if (!((board -> find(positions[i])) == (board -> end()) )) {
				piece = piece_at(board2,positions[i]);
				if ((piece[0] == opponent) && (piece[1] == 'N'))
					return false;
			}
		}

	
	//determine if enemy pawn is in striking distance
	int sign = (colour == 'W')? 1 : -1 ;
	positions.clear();
	positions.push_back(king_x - 1, king_y + sign});
	positions.push_back({king_x + 1, king_y + sign});

	for (i=0; i < 2; ++i){
		if (!((board -> find(positions[i])) == (board -> end()))) {
			piece = piece_at(board2,positions[i]);
			if ((piece[0] == opponent) && (piece[1] == 'P'))
				return false;
		}
	}
	

	//determine if enemy king is in striking distance
	positions.clear();
	positions.push_back({king_x-1, king_y-1});	
	positions.push_back({king_x, king_y-1});
	positions.push_back({king_x+1, king_y-1});
	positions.push_back({king_x-1, king_y});
	positions.push_back({king_x+1, king_y});
	positions.push_back({king_x-1, king_y+1});	
	positions.push_back({king_x, king_y+1});
	positions.push_back({king_x+1, king_y+1});

	for (i = 0; i < 8; ++i)
		if (!((board -> find(positions[i])) == (board -> end()) )) {
			piece = piece_at(board2,positions[i]);
			if ((piece[0] == opponent) && (piece[1] == 'K'))
				return false;
		}
	}
	
	return true;
}

.....................................................................................*/








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
	}
					
	if (!occupied(board,king_end) && !occupied(board,rook_end)){
		unordered_map<string,string> board2 = unordered_map<string,string>(*board); //make copy of board
		update_board(rook_start, rook_end, board2);
		update_board(king_start, king_end, board2);
		
		if (is_king_safe(board2, king_end)){
			update_board(rook_start, rook_end, board);
			update_board(king_start, king_end, board);
			
			player_ps.k_pos = (king_end.to_str());
			player_ps.castle_k_side = false;
			player_ps.castle_q_side = false;
			return true;
		} 		
	}
	return false;
}





