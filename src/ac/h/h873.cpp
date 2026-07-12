#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> A(N), B(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        for (int i = 0; i < N; i++) cin >> B[i];
        
        // Check if multisets are equal
        vector<int> sortedA = A, sortedB = B;
        sort(sortedA.begin(), sortedA.end());
        sort(sortedB.begin(), sortedB.end());
        if (sortedA != sortedB) {
            cout << "no\n";
            continue;
        }
        
        // Store positions of each value in A
        vector<queue<int>> pos(N + 1);
        for (int i = 0; i < N; i++) {
            pos[A[i]].push(i);
        }
        
        // Iterative segment tree for range minimum query
        int n = N;
        vector<int> seg(2 * n);
        for (int i = 0; i < n; i++) seg[n + i] = A[i];
        for (int i = n - 1; i > 0; i--) seg[i] = min(seg[2 * i], seg[2 * i + 1]);
        
        auto update = [&](int idx, int val) {
            idx += n;
            seg[idx] = val;
            for (idx >>= 1; idx > 0; idx >>= 1) {
                seg[idx] = min(seg[2 * idx], seg[2 * idx + 1]);
            }
        };
        
        auto query = [&](int l, int r) {
            int res = INT_MAX;
            for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
                if (l & 1) res = min(res, seg[l++]);
                if (!(r & 1)) res = min(res, seg[r--]);
            }
            return res;
        };
        
        bool ok = true;
        for (int i = 0; i < N; i++) {
            int v = B[i];
            if (pos[v].empty()) { // Should not happen due to multiset check
                ok = false;
                break;
            }
            int p = pos[v].front();
            pos[v].pop();
            
            if (p > 0) {
                int min_left = query(0, p - 1);
                if (min_left < v) {
                    ok = false;
                    break;
                }
            }
            update(p, INT_MAX);
        }
        
        cout << (ok ? "yes" : "no") << '\n';
    }
    
    return 0;
}
