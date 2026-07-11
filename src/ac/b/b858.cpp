#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<int> t(N);
            int total = 0;
            for (int i = 0; i < N; i++) {
                cin >> t[i];
                total += t[i];
            }
            int half = total / 2;
            vector<char> dp(half + 1, 0);
            dp[0] = 1;
            for (int i = 0; i < N; i++) {
                int v = t[i];
                for (int j = half; j >= v; j--) {
                    if (dp[j - v]) dp[j] = 1;
                }
            }
            int best = 0;
            for (int j = half; j >= 0; j--) {
                if (dp[j]) { best = j; break; }
            }
            cout << (total - best) << "\n";
        }
    }
    return 0;
}
