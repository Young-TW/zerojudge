#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n = 0) : n(n), bit(n + 1, 0) {}
    void reset(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int sum(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> A(N), B(N);
        vector<int> all_vals;
        all_vals.reserve(2 * N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i] >> B[i];
            all_vals.push_back(A[i]);
            all_vals.push_back(B[i]);
        }
        
        // Coordinate compression
        sort(all_vals.begin(), all_vals.end());
        all_vals.erase(unique(all_vals.begin(), all_vals.end()), all_vals.end());
        int M = all_vals.size();
        
        auto get_id = [&](int x) {
            return lower_bound(all_vals.begin(), all_vals.end(), x) - all_vals.begin();
        };
        
        // For each value, store positions in B (1-based)
        vector<vector<int>> pos_in_B(M);
        for (int i = 0; i < N; ++i) {
            int id = get_id(B[i]);
            pos_in_B[id].push_back(i + 1);
        }
        
        // For each value, current index in pos_in_B
        vector<int> ptr(M, 0);
        
        // Build permutation P: for each element in A, its target position in B
        vector<int> P(N + 1); // 1-based
        for (int i = 0; i < N; ++i) {
            int id = get_id(A[i]);
            int target_pos = pos_in_B[id][ptr[id]++];
            P[i + 1] = target_pos;
        }
        
        // Count inversions in P
        Fenwick fw(N);
        long long inversions = 0;
        for (int i = 1; i <= N; ++i) {
            int x = P[i];
            inversions += (i - 1) - fw.sum(x);
            fw.add(x, 1);
        }
        
        cout << inversions << '\n';
    }
    
    return 0;
}
