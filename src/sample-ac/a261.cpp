#include <iostream>
#include <climits>
using namespace std;

int main() {
    // dp[t][k] = max floors distinguishable with t trials and k balloons
    // dp[t][k] = dp[t-1][k-1] + dp[t-1][k] + 1
    // Only need t up to 63 (anything beyond -> "More than 63 trials needed.")
    const int MAXT = 64;
    const int MAXK = 101;
    const unsigned long long CAP = ULLONG_MAX;
    static unsigned long long dp[MAXT][MAXK];
    for (int t = 1; t < MAXT; t++) {
        for (int k = 1; k < MAXK; k++) {
            unsigned long long a = dp[t-1][k-1];
            unsigned long long b = dp[t-1][k];
            unsigned long long sum;
            if (b >= CAP - a) {
                sum = CAP;
            } else {
                sum = a + b + 1;
            }
            dp[t][k] = sum;
        }
    }

    int k;
    unsigned long long n;
    while (cin >> k >> n) {
        if (k == 0) break;
        int ans = -1;
        for (int t = 1; t < MAXT; t++) {
            if (dp[t][k] >= n) { ans = t; break; }
        }
        if (ans == -1 || ans > 63) {
            cout << "More than 63 trials needed." << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
