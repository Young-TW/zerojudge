#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        vector<int> a(n + 1);
        a[0] = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        
        vector<long long> dp(n + 1, 1e18);
        vector<int> prev(n + 1, -1);
        dp[0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                long long dist = a[i] - a[j];
                long long penalty = (200 - dist) * (200 - dist);
                if (dp[j] + penalty < dp[i]) {
                    dp[i] = dp[j] + penalty;
                    prev[i] = j;
                }
            }
        }
        
        vector<int> path;
        int curr = n;
        while (curr != -1) {
            path.push_back(curr);
            curr = prev[curr];
        }
        reverse(path.begin(), path.end());
        
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " ";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
