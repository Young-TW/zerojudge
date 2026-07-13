#include <iostream>
#include <vector>

using namespace std;

long long solve(const vector<int>& state, int m, int target) {
    if (m == 0) return 0;
    if (state[m] == target) {
        return solve(state, m - 1, target);
    } else {
        int other = 6 - state[m] - target;
        return solve(state, m - 1, other) + (1LL << (m - 1));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n && n) {
        vector<int> cur(n + 1), tar(n + 1);
        for (int i = 1; i <= n; ++i) cin >> cur[i];
        for (int i = 1; i <= n; ++i) cin >> tar[i];
        
        long long ans = 0;
        for (int k = n; k >= 1; --k) {
            if (cur[k] != tar[k]) {
                int B = 6 - cur[k] - tar[k];
                ans = solve(cur, k - 1, B) + 1 + solve(tar, k - 1, B);
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
