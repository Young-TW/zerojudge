#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        int dp0 = 0, dp1 = 0, dp2 = 0;
        for (int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            int next_dp0 = max(dp0, dp2) + p;
            int next_dp1 = max(dp0, dp2) + 2 * p;
            int next_dp2 = dp1;
            dp0 = next_dp0;
            dp1 = next_dp1;
            dp2 = next_dp2;
        }
        cout << max(dp0, max(dp1, dp2)) << "\n";
    }
    
    return 0;
}
