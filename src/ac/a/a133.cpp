#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N1, N2;
    int caseNo = 0;
    bool first = true;
    while (cin >> N1 >> N2) {
        if (N1 == 0 && N2 == 0) break;
        vector<int> a(N1), b(N2);
        for (int i = 0; i < N1; i++) cin >> a[i];
        for (int i = 0; i < N2; i++) cin >> b[i];
        vector<vector<int>> dp(N1 + 1, vector<int>(N2 + 1, 0));
        for (int i = 1; i <= N1; i++) {
            for (int j = 1; j <= N2; j++) {
                if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        if (!first) cout << "\n";
        first = false;
        caseNo++;
        cout << "Twin Towers #" << caseNo << "\n";
        cout << "Number of Tiles : " << dp[N1][N2] << "\n";
    }
    return 0;
}
