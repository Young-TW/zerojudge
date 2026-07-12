#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void print_int128(__int128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    string s = "";
    while (x > 0) {
        s += (char)('0' + (int)(x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXN = 50000;
    __int128 dp[MAXN + 1] = {0};
    dp[0] = 1;
    int coins[] = {1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000};
    for (int c : coins) {
        for (int i = c; i <= MAXN; ++i) {
            dp[i] += dp[i - c];
        }
    }

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        long long sum = 0;
        long long x;
        bool has_num = false;
        while (ss >> x) {
            sum += x;
            has_num = true;
        }
        if (!has_num) continue;
        if (sum == 0) break;
        print_int128(dp[sum] - 1);
        cout << "\n";
    }

    return 0;
}
