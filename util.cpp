#include "chess.h"
#include <cmath>

/* convert string position representation to cartesian coordinates */
vector<int> to_cart(string pos) {
    assert(pos[0] >= 'a' && pos[0] <= 'h' && pos[0] >= '1' && pos[1] <= '8');
    string cols = "abcdefgh";
    string rows = "12345678";
    vector<int> ret;
    for (int i = 0; i < cols.size(); i++) {
        if (pos[0] == cols[i])
            ret.push_back(i+1);
    }
    for (int i = 0; i < rows.size(); i++) {
        if (pos[1] == rows[i])
            ret.push_back(i+1);
    }
    return ret;
}

/* convert cartesian representation to position string */
string pair_to_str(int x, int y) {
    assert(x>=1 && x<=8 && y >=1 && y <=8);
    string cols = "abcdefgh";
    string rows = "12345678";
    string ret = "";
    ret += cols[x - 1];
    ret += rows[y - 1];
    return ret;
}
string to_str(vector<int> vec) {
    //assert(vec.size() == 2);
    if (vec.size() != 2) {
        throw "to_str wrong size vector";
    }
    return pair_to_str(vec[0], vec[1]);
}


void update_board(vector<int> start, vector<int> end, unordered_map<string, string> *board) {
    (*board)[to_str(end)] = (*board)[to_str(start)];
    (*board)[to_str(start)] = "-";
}

bool occupied(const unordered_map<string, string> *board, vector<int> position){
	return (piece_at(board, position) != "-");
}


/* get piece at pos */
string piece_at(const unordered_map<string, string> *board, vector<int> position) {
    string pos = to_str(position);
    auto got = board->find(pos);
    if (got == board->end())
        throw "key not found in unordered_map";
    return got->second;
}




string piece_at_str(const unordered_map<string, string> *board, string pos) {
    auto got = board->find(pos);
    if (got == board->end())
        throw "key not found in unordered_map";
    return got->second;
}

/* check if the king is in check */
bool king_in_check(const unordered_map<string, string> *board, string king_pos) {
     vector<int> kcarts = to_cart(king_pos);
     char colour = piece_at_str(board, king_pos)[0];

     if (piece_at_str(board, king_pos)[1] != 'K') {
         cerr << "warning: king not at that position" << endl;
     }

     // do vertical check
     for (int x = kcarts[0]+1, y = kcarts[1]; x <= 8; x++) {
         string piece;
         if ((piece = piece_at_str(board,pair_to_str(x,y))) == "-")
             continue;
         else if (piece[0] == colour) // piece is friendly
             break;
         else if (piece[1] == 'R' || piece[1] == 'Q' ) // piece is rook or queen
             return true;
         else  // it is some other piece that cannot attack horizontally or vertically
             break;
     }
     for (int x = kcarts[0]-1, y = kcarts[1]; x >= 1; x--) {
         string piece;
         if ((piece = piece_at_str(board,pair_to_str(x,y))) == "-")
             continue;
         else if (piece[0] == colour) // piece is friendly
             break;
         else if (piece[1] == 'R' || piece[1] == 'Q' ) // piece is rook or queen
             return true;
         else  // it is some other piece that cannot attack horizontally or vertically
             break;
     }
     // do vertical check
     for (int x = kcarts[0], y = kcarts[1]+1; y <= 8; y++) {
         string piece;
         if ((piece = piece_at_str(board,pair_to_str(x,y))) == "-") 
             continue;
         else if (piece[0] == colour) // piece is friendly 
             break;
         else if (piece[1] == 'R' || piece[1] == 'Q' ){ // piece is rook or queen
             return true;
         }
         else  // it is some other piece that cannot attack horizontally or vertically
             break;
     }
     for (int x = kcarts[0], y = kcarts[1]-1; y >= 1; y--) {
         string piece;
         if ((piece = piece_at_str(board,pair_to_str(x,y))) == "-")
             continue;
         else if (piece[0] == colour) // piece is friendly
             break;
         else if (piece[1] == 'R' || piece[1] == 'Q' ) // piece is rook or queen
             return true;
         else  // it is some other piece that cannot attack horizontally or vertically
             break;
     }
     // do digaonal check
     for (int x = kcarts[0]+1, y = kcarts[1]+1; x<=8 && y<=8; x++, y++) {
         string piece;
         if ((piece = piece_at_str(board,pair_to_str(x,y))) == "-")
             continue;
         else if (piece[0] == colour) // piece is friendly
             break;
         else if (piece[1] == 'B' || piece[1] == 'Q' )// piece bishop or queen
             return true;
         else  // it is some other piece that cannot attack diagonally
             break;
     }
     for (int x = kcarts[0]-1, y = kcarts[1]-1; x>=1 && y>=1; x--, y--) {
         string piece;
         if ((piece = piece_at_str(board,pair_to_str(x,y))) == "-")
             continue;
         else if (piece[0] == colour) // piece is friendly
             break;
         else if (piece[1] == 'B' || piece[1] == 'Q' )// piece bishop or queen
             return true;
         else  // it is some other piece that cannot diagonally
             break;
     }
     for (int x = kcarts[0]+1, y = kcarts[1]-1; x<=8 && y>=1; x++, y--) {
         string piece;
         if ((piece = piece_at_str(board,pair_to_str(x,y))) == "-")
             continue;
         else if (piece[0] == colour) // piece is friendly
             break;
         else if (piece[1] == 'B' || piece[1] == 'Q' )// piece bishop or queen
             return true;
         else  // it is some other piece that cannot attack diagonally
             break;
     }
     for (int x = kcarts[0]-1, y = kcarts[1]+1; x>=1 && y<=8; x--, y++) {
         string piece;
         if ((piece = piece_at_str(board,pair_to_str(x,y))) == "-")
             continue;
         else if (piece[0] == colour) // piece is friendly
             break;
         else if (piece[1] == 'B' || piece[1] == 'Q' )// piece bishop or queen
             return true;
         else  // it is some other piece that cannot diagonally
             break;
     }
     // do knight check
     string piece;
     int x,y;
     for (int i = 1; i <= 2; i++) {
         for (int j = 1; j <=2; j++) {
             if ((x = kcarts[0]+ pow(-1,i)*2) <=8 && (y = kcarts[1] + pow(-1,j)*1) <=8) {
                 piece = piece_at_str(board, pair_to_str(x,y));
                 if (piece[1] == 'N' && piece[0] != colour) {
                     return true;
                 }
             }
         }
     }
     for (int i = 1; i <= 2; i++) {
         for (int j = 1; j <=2; j++) {
             if ((x = kcarts[0]+ pow(-1,i)*1) <=8 && (y = kcarts[1] + pow(-1,j)*2) <=8) {
                 piece = piece_at_str(board, pair_to_str(x,y));
                 if (piece[1] == 'N' && piece[0] != colour) {
                     return true;
                 }
             }
         }
     }

     return false;
  }












