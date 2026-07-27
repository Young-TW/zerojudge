#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // matchsticks needed for digits 0..9
    const int sticks[10] = {6,2,5,5,4,5,6,3,7,6};

    // best[t] = largest integer (as string) that uses exactly t sticks
    vector<string> best(51, "");

    // enumerate all non‑empty subsets of digits
    for (int mask = 1; mask < (1 << 10); ++mask) {
        int sum = 0;
        string s;
        // digits in descending order
        for (int d = 9; d >= 0; --d) {
            if (mask & (1 << d)) {
                sum += sticks[d];
                s.push_back(char('0' + d));
            }
        }
        if (sum > 50) continue;
        if (best[sum].empty() ||
            s.size() > best[sum].size() ||
            (s.size() == best[sum].size() && s > best[sum])) {
            best[sum] = s;
        }
    }

    int n;
    while (cin >> n) {
        if (n < 0 || n > 50 || best[n].empty())
            cout << -1 << '\n';
        else
            cout << best[n] << '\n';
    }
    return 0;
}
