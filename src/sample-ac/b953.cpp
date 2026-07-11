#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int lcs2(const string& s1, const string& s2) {
    int n1 = s1.size();
    int n2 = s2.size();
    vector<int> dp(n2 + 1, 0);
    for (int i = 1; i <= n1; ++i) {
        int prev = 0;
        char c1 = s1[i-1];
        for (int j = 1; j <= n2; ++j) {
            int temp = dp[j];
            if (c1 == s2[j-1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = max(dp[j], dp[j-1]);
            }
            prev = temp;
        }
    }
    return dp[n2];
}

int lcs3(const string& s1, const string& s2, const string& s3) {
    int n1 = s1.size();
    int n2 = s2.size();
    int n3 = s3.size();
    int W = n3 + 1;
    vector<int> dp((n2 + 1) * W, 0);
    vector<int> next_dp((n2 + 1) * W, 0);
    for (int i = 1; i <= n1; ++i) {
        char c1 = s1[i-1];
        for (int j = 1; j <= n2; ++j) {
            char c2 = s2[j-1];
            bool match12 = (c1 == c2);
            int base_curr = j * W;
            int base_prev = (j - 1) * W;
            for (int k = 1; k <= n3; ++k) {
                if (match12 && c2 == s3[k-1]) {
                    next_dp[base_curr + k] = dp[base_prev + k - 1] + 1;
                } else {
                    next_dp[base_curr + k] = max(max(dp[base_curr + k], next_dp[base_prev + k]), next_dp[base_curr + k - 1]);
                }
            }
        }
        swap(dp, next_dp);
    }
    return dp[n2 * W + n3];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        if (n == 2) {
            string s1, s2;
            cin >> s1 >> s2;
            cout << lcs2(s1, s2) << "\n";
        } else if (n == 3) {
            string s1, s2, s3;
            cin >> s1 >> s2 >> s3;
            cout << lcs3(s1, s2, s3) << "\n";
        }
    }
    return 0;
}
