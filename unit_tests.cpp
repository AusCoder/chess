#include "chess.h"

int main() {
    vector<string> positions {"a1", "h1", "a8", "h8"};
    for (auto it = positions.begin(); it != positions.end(); it++) {
        cout << *it << " " << "( " ;
        vector<int> carts = to_cart(*it);
        for (auto jt = carts.begin(); jt != carts.end(); jt++) {
            cout << *jt << " ";
        }
        cout << ")" << endl;
    }
    return 0;
}
