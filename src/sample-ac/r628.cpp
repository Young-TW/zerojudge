#include <iostream>
#include <vector>

using namespace std;

struct BIT {
    int n;
    vector<int> tree;
    BIT(int n = 0) : n(n), tree(n + 1, 0) {}
    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) tree[idx] += val;
    }
    int query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += tree[idx];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> P(n + 1), pos(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> P[i];
            pos[P[i]] = i;
        }
        
        vector<int> L(n + 1);
        BIT bit(n);
        for (int val = n; val >= 1; --val) {
            L[val] = bit.query(pos[val] - 1);
            bit.update(pos[val], 1);
        }
        
        long long ans = 0;
        int prev = 0; // L_0 = 0
        for (int k = 1; k <= n; ++k) {
            if (prev > L[k]) ans += prev - L[k];
            else ans += 1 + L[k] - prev;
            prev = L[k];
        }
        cout << ans << '\n';
    }
    return 0;
}
