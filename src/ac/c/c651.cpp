#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, Q;
    while (cin >> N >> Q) {
        vector<int> bit(N + 1, 0);
        vector<int> arr(N + 1, 0);
        
        auto update = [&](int i, int val) {
            for (; i <= N; i += i & -i)
                bit[i] ^= val;
        };
        
        auto query = [&](int i) {
            int res = 0;
            for (; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        };
        
        for (int i = 1; i <= N; ++i) {
            cin >> arr[i];
            update(i, arr[i]);
        }
        
        for (int i = 0; i < Q; ++i) {
            int op;
            cin >> op;
            if (op == 0) {
                int l, r;
                cin >> l >> r;
                cout << (query(r) ^ query(l - 1)) << '\n';
            } else {
                int x, v;
                cin >> x >> v;
                update(x, arr[x] ^ v);
                arr[x] = v;
            }
        }
    }
    return 0;
}
