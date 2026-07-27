#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // read three non‑empty lines that contain digits
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        bool hasDigit = false;
        for (char c : line) if (isdigit(c) || c == '-') { hasDigit = true; break; }
        if (hasDigit) lines.push_back(line);
    }
    if (lines.size() < 3) return 0;               // no valid input

    // parse weights
    vector<int> w;
    {
        stringstream ss(lines[0]);
        int x;
        while (ss >> x) w.push_back(x);
    }
    // parse values
    vector<int> v;
    {
        stringstream ss(lines[1]);
        int x;
        while (ss >> x) v.push_back(x);
    }
    // parse capacity
    long long Lll = 0;
    {
        stringstream ss(lines[2]);
        ss >> Lll;
    }
    int L = static_cast<int>(Lll);                // L ≤ 1 000 000 fits in int

    int n = static_cast<int>(w.size());
    if ((int)v.size() != n) return 0;             // malformed input

    vector<int> dp(L + 1, 0);                     // dp[c] = best value for capacity c

    for (int i = 0; i < n; ++i) {
        int wi = w[i];
        int vi = v[i];
        if (wi > L) continue;                     // cannot be taken at all
        for (int c = L; c >= wi; --c) {
            int cand = dp[c - wi] + vi;
            if (cand > dp[c]) dp[c] = cand;
        }
    }

    cout << dp[L] << '\n';
    return 0;
}
