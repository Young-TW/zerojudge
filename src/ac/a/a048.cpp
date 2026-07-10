#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, Q;
    while (cin >> N >> Q) {
        vector<int> bit(N + 1, 0);
        auto upd = [&](int i) {
            for (; i <= N; i += i & (-i)) bit[i] ^= 1;
        };
        auto qry = [&](int i) {
            int s = 0;
            for (; i > 0; i -= i & (-i)) s ^= bit[i];
            return s;
        };
        while (Q--) {
            int v;
            cin >> v;
            if (v == 1) {
                int i;
                cin >> i;
                upd(i);
            } else {
                int L, R;
                cin >> L >> R;
                int res = qry(R) ^ qry(L - 1);
                cout << res << '\n';
            }
        }
    }
    return 0;
}
