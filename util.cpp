#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

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

/* get piece at pos */
string piece_at(const unordered_map<string, string> *board, string pos) {
    auto got = board->find(pos);
    if (got == board->end())
        throw "key not found in unordered_map";
    return got->second;
}

