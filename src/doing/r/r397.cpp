#include <iostream>
#include <vector>
#include <algorithm>

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
    
    int N;
    while (cin >> N) {
        vector<pair<long long, long long>> pts(N);
        for (int i = 0; i < N; ++i) {
            cin >> pts[i].first >> pts[i].second;
        }
        
        // Count identical pairs
        sort(pts.begin(), pts.end());
        long long ans = 0;
        for (int i = 0; i < N; ) {
            int j = i;
            while (j < N && pts[j] == pts[i]) ++j;
            long long cnt = j - i;
            ans += cnt * (cnt - 1) / 2;
            i = j;
        }
        
        // Coordinate compression for y
        vector<long long> ys;
        ys.reserve(N);
        for (auto &p : pts) ys.push_back(p.second);
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        
        BIT bit(ys.size());
        
        // Count strict dominance pairs (x_i < x_j and y_i < y_j)
        for (int i = 0; i < N; ) {
            int j = i;
            while (j < N && pts[j].first == pts[i].first) ++j;
            
            // Query for all points in this x-group
            for (int k = i; k < j; ++k) {
                int y_idx = lower_bound(ys.begin(), ys.end(), pts[k].second) - ys.begin() + 1;
                ans += bit.query(y_idx - 1);
            }
            // Update after querying the whole group
            for (int k = i; k < j; ++k) {
                int y_idx = lower_bound(ys.begin(), ys.end(), pts[k].second) - ys.begin() + 1;
                bit.update(y_idx, 1);
            }
            i = j;
        }
        
        cout << ans << '\n';
    }
    return 0;
}
