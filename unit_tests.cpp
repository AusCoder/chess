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

    vector<int> a1 {1,1};
    vector<int> a8 {1,8};
    vector<int> h1 {8,1};
    vector<int> h8 {8,8};
    cout << "expected: a1" << " "  << to_str(a1[0],a1[1]) << endl;
    cout << "expected: a8" << " "  << to_str(a8[0],a8[1]) << endl;
    cout << "expected: h1" << " "  << to_str(h1[0],h1[1]) << endl;
    cout << "expected: h8" << " "  << to_str(h8[0], h8[1]) << endl;

    return 0;
}
