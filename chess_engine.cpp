#include <iostream>
#include <unordered_map>
#include <string>

#include "chess.h"

using namespace std;

int main() {

    bool white_turn = true; //0 if white's turn; 1 if black's
    unordered_map<string, string> *board = new unordered_map<string, string>;

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
