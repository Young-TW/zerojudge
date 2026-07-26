#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2;
    while (cin >> s1 >> s2) {
        int N;
        if (!(cin >> N)) break;
        vector<pair<char, char>> ops(N);
        for (int i = 0; i < N; ++i) {
            char x, y;
            cin >> x >> y;
            ops[i] = {x, y};
        }

        // final mapping for each letter
        char finalMap[26];
        for (int c = 0; c < 26; ++c) {
            char cur = static_cast<char>('a' + c);
            for (int i = 0; i < N; ++i) {
                if (cur == ops[i].first) cur = ops[i].second;
            }
            finalMap[c] = cur;
        }

        int diff = 0;
        for (size_t i = 0; i < s1.size(); ++i) {
            char after = finalMap[s1[i] - 'a'];
            if (after != s2[i]) ++diff;
        }
        cout << diff << '\n';
    }
    return 0;
}
