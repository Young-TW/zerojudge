#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long solve_same(const vector<int>& X, const vector<int>& Y) {
    int N = X.size();
    int M = Y.size();
    long long ans = -1e18;
    for (int d = -(N - 1); d <= M - 1; ++d) {
        long long cur = 0;
        long long best = -1e18;
        int start_t = max(0, -d);
        int end_t = min(N - 1, M - 1 - d);
        for (int t = start_t; t <= end_t; ++t) {
            long long val = (long long)X[t] * Y[t + d];
            cur = max(val, cur + val);
            best = max(best, cur);
        }
        ans = max(ans, best);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> A(n);
        vector<int> B(m);
        for (int i = 0; i < n; ++i) cin >> A[i];
        for (int i = 0; i < m; ++i) cin >> B[i];
        
        long long ans1 = solve_same(A, B);
        
        vector<int> revB = B;
        reverse(revB.begin(), revB.end());
        long long ans2 = solve_same(A, revB);
        
        cout << max(ans1, ans2) << "\n";
    }
    return 0;
}
