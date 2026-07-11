#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    multiset<int> s;
    int xor_val = 0;

    while (Q--) {
        int t, k;
        cin >> t >> k;

        if (t == 1) {
            s.insert(k ^ xor_val);
        } else if (t == 2) {
            auto it = s.find(k ^ xor_val);
            if (it == s.end()) {
                cout << "HEHE\n";
            } else {
                s.erase(it);
            }
        } else if (t == 3) {
            if (k > s.size()) {
                cout << "QQ\n";
            } else {
                auto it = s.begin();
                advance(it, k - 1);
                cout << (*it ^ xor_val) << '\n';
            }
        } else if (t == 4) {
            xor_val ^= k;
        }
    }

    return 0;
}
