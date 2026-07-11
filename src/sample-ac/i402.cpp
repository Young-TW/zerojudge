#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long solve(const vector<int>& A, const vector<int>& B) {
    int n = A.size();
    int m = B.size();
    long long max_val = -1e18;
    for (int d = -(m - 1); d <= n - 1; ++d) {
        long long current_sum = 0;
        bool has_element = false;
        int start_i = max(0, d);
        int end_i = min(n - 1, m - 1 + d);
        for (int i = start_i; i <= end_i; ++i) {
            int j = i - d;
            long long val = (long long)A[i] * B[j];
            if (!has_element) {
                current_sum = val;
                has_element = true;
            } else {
                current_sum = max(val, current_sum + val);
            }
            if (current_sum > max_val) {
                max_val = current_sum;
            }
        }
    }
    return max_val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    while (cin >> n >> m) {
        vector<int> A(n), B(m);
        for (int i = 0; i < n; ++i) cin >> A[i];
        for (int i = 0; i < m; ++i) cin >> B[i];
        
        long long ans = -1e18;
        ans = max(ans, solve(A, B));
        reverse(B.begin(), B.end());
        ans = max(ans, solve(A, B));
        
        cout << ans << "\n";
    }
    return 0;
}
