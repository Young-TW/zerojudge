#include <bits/stdc++.h>
using namespace std;

// check whether all characters of pat appear in s in order
bool isSubsequence(const string &s, const string &pat) {
    size_t pos = 0;
    for (char c : s) {
        if (c == pat[pos]) {
            ++pos;
            if (pos == pat.size()) break;
        }
    }
    return pos == pat.size();
}

// true if the string consists only of capital letters A..Z
bool isAllUpper(const string &s) {
    for (char c : s) if (c < 'A' || c > 'Z') return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string token;
    while (cin >> token) {
        string label, P, T;
        int N;
        if (!isAllUpper(token)) {               // token is a label line
            label = token;
            if (!(cin >> P >> T >> N)) break;
        } else {                                 // token is actually P
            label.clear();
            P = token;
            if (!(cin >> T >> N)) break;
        }

        vector<int> lengths;
        int n = (int)T.size();
        int m = (int)P.size();

        for (int i = 0; i < n; ++i) {
            if (T[i] != P[0]) continue;
            for (int j = i; j < n; ++j) {
                if (T[j] != P[m - 1]) continue;
                // quick length check
                if (j - i + 1 < m) continue;
                if (isSubsequence(T.substr(i, j - i + 1), P))
                    lengths.push_back(j - i + 1);
            }
        }

        sort(lengths.begin(), lengths.end(), greater<int>());
        long long ans = 0;
        int take = min(N, (int)lengths.size());
        for (int i = 0; i < take; ++i) ans += lengths[i];

        if (!label.empty()) cout << label << '\n';
        cout << ans << '\n';
    }
    return 0;
}
