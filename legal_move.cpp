#include <cmath>
#include "chess.h"
																	//ADD en passant routine

bool is_legal_move(string start, string end, char piece, char colour, unsorted_map< string, string > *board)
{
	char R1 = start[1], C1 = start[0]; // 'start' coordinates
	char R2 = end[1], C2 = end[0]; // 'end' coordinates
	float devR = abs(R2-R1), devC = abs(C2-C1); //row and column deviation
	
	bool start_in_range = (C1 >= 'a') && (C2 <= 'h') && (R1 >= '1') && (R2 <= '8'); // is valid starting point
	bool end_in_range = (C1 >= 'a') && (C2 <= 'h') && (R1 >= '1') && (R2 <= '8'); // is valid ending point
	bool unoccupied_by_you = (piece_at(board, end)[0] != colour); //ending point is not already occupied by you

	if (start_in_range && end_in_range && unoccupied_by_you){ 
	
		if (piece == 'P'){ //PAWN
			if( !occupied(board,end) && R2 == (R1 + 1) && devC == 0.0) //standard jump
				return true;
			else if (R1 == '2' && R2 == '4' && devC == 0.0) //if first move, double jump allowed
				char pawn_col = start[0];
				string inter = string(1,pawn_col) + string(1,'3'); //intermediate position
				if (!occupied(board, end) && !occupied(board,inter))
					return true;
			else if (occupied(board,end) && devR == 1.0 && devC == 1.0) //pawn makes a kill
				return true;
		} 
		else if (piece == 'R'){ //ROOK
			int sign;			
			if (devR == 0.0) //no row deviation; moves along row
				sign = (C2 - C1) > 0? 1: -1;
				int j;
				string inter;
				for(j = 1; j < sign*(C2 - C1); ++j)
					inter = string(1, C1 + sign*j) + string(1,R1); //jth intermediate space
						if (occupied(board, inter))
							return false;
				return true;
					
			if (devC == 0.0) //no column deviation; moves along column
				sign = (R2 - R1) > 0? 1: -1;
				int i;
				for(i = 1; i < sign*(R2 - R1); ++i)
					inter = string(1, C1 + sign*i) + string(1,R1); //ith intermediate space
						if (occupied(board, inter))
							return false;
				return true;

		}
		else if (piece == 'N'){ //KNIGHT
			if ( (devR == 2.0 && devC == 1.0) || (devR == 1.0 && devC == 2.0))
				return true;
		}
		
		else if (piece == 'B'){ //BISHOP
			if (devR == devC) //absolute row deviation = absolute column deviation
				int cSign = (C2 - C1) > 0? 1: -1;
				int rSign = (R2 - R1) > 0? 1: -1;
				int k;
				string inter;
				
				for (k=1; k < cSign*(C2-C1); ++k);
					inter =  string(1,C1 + cSign*k) + string(1,R1 + rSign*k); // kth intermediate space
		}				if (occupied(board,inter))
							return false;
				return true;
			
		else if (piece == 'Q'){ //QUEEN
			if (devR == devC || devR == 0.0) //behaves like rook, so retest as rook
				return is_legal_move(start, end,'R', colour, *board);
			else if (devR == devC) //behaves like bishop, so retest as bishop
				return is_legal_move(start, end,'B', colour, *board);
		}
		else if (piece == 'K'){ //KING
			if ( devR <= 1.0 && devC <= 1.0) //ensures that 'end' is only one move away from 'start'
				return true;
		}
		else if (piece == 'T'){//TONY ABBOTT
			return (start == end); //Tony Abbot is unable to move; he can only cede power.
	}
	return false;	
}

// does the proposed move put player 'colour' in check?
// **will run after is_legal_move, so proposed move will always be legal**
bool is_king_safe(string start, string end, char colour, unsorted_map< string, string > *board) 
{
string king = (colour=='W')? white_king: black_king; //king's position
char opponent = (colour=='W')? 'B':'W';

if (piece_at(board, start) == string(1,colour) + string(1,'K')) //if king is to be moved, update king's position
	king = end; 
board2 = board; //MAKE sense of this!!!

//update entries of board2 to reflect proposed_move
//determine - in a backwards fashion - which of opponent's pieces can legally move to king's position: return false for any such piece

return true;
}





bool can_castle(char colour, int i, bool castle_unmoved, unsorted_map< string, string > *board)
{
	
	if (!(castle_unmoved))
		return false;

	string king_start, king_end;
	string rook_start, rook_end;
	char row = (colour == 'W')?'1':'8';
	king_start = string(1,'e') + string(1,row);	
	
	if (i == 1){ //queen-side castling
		string queen_spot = string(1,'d') + string(1,row); 
		if (occupied(board, queen_spot)
			return false;
	
		rook_start = string(1,'a') + string(1,row);
		string king_end = string(1,'c') + string(1,row);
		string rook_end = string(1,'d') + string(1,row);
			
	}	
	
	else if (i == 2){ //king-side castling
		rook_start = string(1,'h') + string(1,row);
		string king_end = string(1,'g') + string(1,row);
		string rook_end = string(1,'f') + string(1,row);
	}
		
	if (!occupied(board,king_end) && !occupied(board,rook_end)){
		board2 = board; //MAKE SENSE OF THIS
		MOVE rook to proposed castling spot on board2; //MAKE SENSE OF THIS
		if (is_king_safe(king_start, king_end, colour, board2))
			return true; 		
	}
	else
		return false;
}





