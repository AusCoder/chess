#include "chess.h"

/* convert string position representation to cartesian coordinates */
vector<int> to_cart(string pos) {
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
string to_str(int x, int y) {
    string cols = "abcdefgh";
    string rows = "12345678";
    string ret = "";
    ret += cols[x - 1];
    ret += rows[y - 1];
    return ret;
}
/*
string to_str(vector<int> cart) {
    if (cart.size() != 2)
        cerr << "warning: cartesian coordinates do not have 2 complonents!" << endl;
    string cols = "abcdefgh";
    string rows = "12345678";
    string ret = "";
    ret += cols[cart[0] - 1];
    ret += rows[cart[1] - 1];
    return ret;
}
*/

/* get piece at pos */
string piece_at(const unordered_map<string, string> *board, string pos) {
    auto got = board->find(pos);
    if (got == board->end())
        throw "key not found in unordered_map";
    return got->second;
}

/* check if the king is in check */
bool king_in_check(const unordered_map<string, string> *board, string king_pos) {
    vector<int> kcarts = to_cart(king_pos);
    char colour = piece_at(board, king_pos)[0];

    /* do horizontal checks */
    for (int x = kcarts[0]+1, y = kcarts[1]; x <= 8; x++) 
        string piece;
        if ((piece = piece_at(board,to_str(x,y))) == "-") // pieve
            continue;
        if (piece[0] == colour) // piece is friendly
            break;
    }
    return true;
}
