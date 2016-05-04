#include <cmath>
#include "chess.h"

bool first_move;

// bool clear_path(string start, string end, char piece) {access hashmap; return true if no obstruction to proposed move}
// bool puts_in_check()

bool abstract_legal(string start, string end, char piece) // e.g., input = ("e4", "f5", 'B')
{
	int R1 = start[1], C1 = start[0]; // 'start' coordinates
	int R2 = end[1], C2 = end[0]; // 'end' coordinates
	int devR = abs(R2-R1), devC = abs(C2-C1); //row and column deviation
	bool start_in_range = (C1 >= 'a') && (C2 <= 'h') && (R1 >= '1') && (R2 <= '8'); // is valid starting point
	bool end_in_range = (C1 >= 'a') && (C2 <= 'h') && (R1 >= '1') && (R2 <= '8'); // is valid ending point
	

	if (start_in_range && end_in_range){ // piece is starting from /ending at a place off the board
		
		if (piece == 'P'){ //pawn
			if( R2 == (R1 + 1) && devC == 0.0)
				return true;
			else if (first_move && R2 == (R1 + 2) && devC == 0.0) //if first move, double jump allowed
				return true;
		} 
		else if (piece == 'R'){ //rook
			if (devR == 0.0 || devC == 0.0) //no deviation in either column or row
				return true;
		}
		else if (piece == 'N'){ //knight
			if ( (devR == 2.0 && devC == 1.0) || (devR == 1.0 && devC == 2.0))
				return true;
		}
		
		else if (piece == 'B'){ //bishop
			if (devR == devC) //row deviation = column deviation
				return true;
		}
		else if (piece == 'Q'){ // queen
			if (devR == devC || devR == 0.0 || devC == 0.0) // rook or bishop conditions are satisfied
				return true;
		}
		else if (piece == 'K'){ //king
			if ( devR <= 1.0 && devC <= 1.0) //ensures that 'end' is only one move away from 'start'
				return true;
		}
	}
	return false;	
}
