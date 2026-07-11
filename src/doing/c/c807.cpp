#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        multiset<long long> s;
        for (int i = 0; i < N; ++i) {
            int op;
            cin >> op;
            if (op == 1) {
                long long x;
                cin >> x;
                s.insert(x);
            } else if (op == 2) {
                long long l, r;
                cin >> l >> r;
                auto it_l = s.lower_bound(l);
                auto it_r = s.upper_bound(r);
                s.erase(it_l, it_r);
            }
            
            if (s.empty()) {
                cout << "0\n";
            } else if (s.size() == 1) {
                cout << "1 " << *s.begin() << "\n";
            } else {
                cout << "2 " << *s.begin() << " " << *s.rbegin() << "\n";
            }
        }
    }
    return 0;
}
