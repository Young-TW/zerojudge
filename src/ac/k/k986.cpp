#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

const int sticks[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

string get_min_number(int n) {
    if (n == 2) return "1";
    if (n == 3) return "7";
    if (n == 4) return "4";
    if (n == 5) return "2";
    if (n == 6) return "6";
    if (n == 7) return "8";

    vector<string> dp(n + 1, "99999999999999999999999999999999");
    dp[0] = "";
    for (int i = 1; i <= n; ++i) {
        for (int d = 0; d <= 9; ++d) {
            if (sticks[d] > i) continue;
            if (i == sticks[d] && d == 0) continue;
            string prev = dp[i - sticks[d]];
            if (prev == "99999999999999999999999999999993") continue;
            string candidate = prev + to_string(d);
            if (candidate.size() < dp[i].size() ||
                (candidate.size() == dp[i].size() && candidate < dp[i])) {
                dp[i] = candidate;
            }
        }
    }
    return dp[n];
}

string get_max_number(int n) {
    if (n % 2 == 0) {
        return string(n / 2, '1');
    } else {
        return "7" + string((n - 3) / 2, '1');
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string min_num = get_min_number(n);
        string max_num = get_max_number(n);
        cout << min_num << " " << max_num << endl;
    }
    return 0;
}
