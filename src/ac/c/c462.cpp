#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long k;
    string s;
    while (cin >> k) {
        if (!(cin >> s)) break;
        int n = static_cast<int>(s.size());
        vector<int> upPref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            upPref[i + 1] = upPref[i] + (isupper(static_cast<unsigned char>(s[i])) ? 1 : 0);
        }

        int bestBlocks = 0;                     // maximal number of alternating blocks
        for (int r = 0; r < k; ++r) {
            int curLen = 0;                     // length of current alternating run (in blocks)
            int prevCase = -2;                  // previous block case, -2 = undefined
            for (int i = r; i + k <= n; i += static_cast<int>(k)) {
                int up = upPref[i + k] - upPref[i];
                int curCase;
                if (up == 0)          curCase = 0;          // all lower
                else if (up == k)    curCase = 1;          // all upper
                else                 curCase = -1;         // mixed -> invalid

                if (curCase == -1) {
                    curLen = 0;
                    prevCase = -2;
                } else {
                    if (curLen == 0) {
                        curLen = 1;
                    } else if (curCase != prevCase) {
                        ++curLen;
                    } else {
                        curLen = 1;               // start new run at this block
                    }
                    prevCase = curCase;
                    if (curLen > bestBlocks) bestBlocks = curLen;
                }
            }
        }
        cout << static_cast<long long>(bestBlocks) * k << '\n';
    }
    return 0;
}
