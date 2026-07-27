#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        int n = static_cast<int>(s.size());
        vector<int> d(n);
        for (int i = 0; i < n; ++i) d[i] = s[i] - '0';

        // first maximum
        int a = -1, idx = -1;
        for (int i = 0; i < n; ++i) {
            if (d[i] > a) {
                a = d[i];
                idx = i;
            }
        }

        // second maximum (different position)
        d[idx] = -1;               // remove the first occurrence
        int b = -1;
        for (int i = 0; i < n; ++i) {
            if (d[i] > b) b = d[i];
        }

        int sumSq = a * a + b * b;

        // last three digits as integer
        int tail = 0;
        int start = max(0, n - 3);
        for (int i = start; i < n; ++i) {
            tail = tail * 10 + (s[i] - '0');
        }

        if (sumSq == tail)
            cout << "Good Morning!\n";
        else
            cout << "SPY!\n";
    }
    return 0;
}
