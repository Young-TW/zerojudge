#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int K, Q;
    while (cin >> K >> Q) {
        unsigned long long max_node = (1ULL << K) - 1;
        while (Q--) {
            int o;
            unsigned long long x;
            cin >> o >> x;
            unsigned long long low = x & -x;
            if (o == 1) {
                unsigned long long t = x / low;
                unsigned long long p;
                if (t % 4 == 1) p = x + low;
                else p = x - low;
                if (p >= 1 && p <= max_node) cout << p << '\n';
                else cout << "-1\n";
            } else if (o == 2) {
                if (low == 1) cout << "-1\n";
                else cout << x - (low >> 1) << '\n';
            } else if (o == 3) {
                if (low == 1) cout << "-1\n";
                else cout << x + (low >> 1) << '\n';
            } else if (o == 4) {
                if (x >= 3 * low) cout << x - 2 * low << '\n';
                else cout << "-1\n";
            } else if (o == 5) {
                unsigned long long nxt = x + 2 * low;
                if (nxt <= max_node) cout << nxt << '\n';
                else cout << "-1\n";
            } else if (o == 6) {
                unsigned long long size = (low << 1) - 1;
                cout << x * size << '\n';
            }
        }
    }
    return 0;
}
