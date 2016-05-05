#include <cmath>
#include "chess.h"
																	//ADD castling and en passant

bool legal_move(string start, string end, char piece, char colour, unsorted_map< string, string > *board)
{
	int R1 = start[1], C1 = start[0]; // 'start' coordinates
	int R2 = end[1], C2 = end[0]; // 'end' coordinates
	float devR = abs(R2-R1), devC = abs(C2-C1); //row and column deviation
	
	bool start_in_range = (C1 >= 'a') && (C2 <= 'h') && (R1 >= '1') && (R2 <= '8'); // is valid starting point
	bool end_in_range = (C1 >= 'a') && (C2 <= 'h') && (R1 >= '1') && (R2 <= '8'); // is valid ending point
	bool unoccupied_by_you = (piece_at(board, end)[0] != colour); //ending point is not already occupied by you

	if (start_in_range && end_in_range && unoccupied_by_you){ 
	
		if (piece == 'P'){ //PAWN
			if( !occupied(board,end) && R2 == (R1 + 1) && devC == 0.0) //standard jump
				return true;
			else if (R1 == '2' && R2 == '4' && devC == 0.0) //if first move, double jump allowed
				if (!occupied(board, end) && true) 									//obstruction check FIX!!!
					return true;
			else if (occupied(board,end) && devR == 1.0 && devC == 1.0) //pawn makes a kill
				return true;
		} 
		else if (piece == 'R'){ //ROOK
			if (devR == 0.0 || devC == 0.0) //no deviation in column or no deviation in row
				if(true) 												//obstruction check FIX!!!
					return true;
		}
		else if (piece == 'N'){ //KNIGHT
			if ( (devR == 2.0 && devC == 1.0) || (devR == 1.0 && devC == 2.0))
				return true;
		}
		
		else if (piece == 'B'){ //BISHOP
			if (devR == devC) //row deviation = column deviation
				if(true) 												//obstruction check FIX!!!
					return true;
		}
		else if (piece == 'Q'){ //QUEEN
			if (devR == devC || devR == 0.0) //behaves like rook, so retest as rook
				return legal_move(string start, string end, char 'R', char colour, unsorted_map< string, string > *board);
			else if (devR == devC) //behaves like bishop, so retest as bishop
				return legal_move(string start, string end, char 'B', char colour, unsorted_map< string, string > *board);
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
