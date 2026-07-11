#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, n;
    while (cin >> V >> n) {
        vector<int> dp(V + 1, 0);
        for (int i = 0; i < n; ++i) {
            int v;
            cin >> v;
            for (int j = V; j >= v; --j) {
                dp[j] = max(dp[j], dp[j - v] + v);
            }
        }
        cout << V - dp[V] << "\n";
    }
    return 0;
}
