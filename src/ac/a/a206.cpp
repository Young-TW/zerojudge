#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const string REL = "This is a reliable sorting ghost leg!";
    const string NOT = "So sad......This is just a  ghost leg.";

    int n, m;
    while (cin >> n >> m) {
        int x;
        if (!(cin >> x)) break;

        vector<vector<long long>> tests(x, vector<long long>(n));
        for (int i = 0; i < x; ++i)
            for (int j = 0; j < n; ++j)
                cin >> tests[i][j];

        vector<string> pic(n);
        for (int i = 0; i < n; ++i) cin >> pic[i];

        /* build comparator list */
        struct Comp { int up, down; };
        vector<Comp> comps;

        for (int col = 0; col < m; ++col) {
            int row = 0;
            while (row < n) {
                char ch = (col < (int)pic[row].size()) ? pic[row][col] : '-';
                if (ch >= 'A' && ch <= 'Z') {
                    char letter = ch;
                    int start = row;
                    int r = row;
                    while (r + 1 < n) {
                        char nxt = (col < (int)pic[r + 1].size()) ? pic[r + 1][col] : '-';
                        if (nxt == letter) ++r;
                        else break;
                    }
                    int end = r;
                    if (end > start) comps.push_back({start, end});
                    row = end + 1;
                } else {
                    ++row;
                }
            }
        }

        bool reliable = true;
        for (const auto &vec : tests) {
            vector<long long> v = vec;
            for (const auto &c : comps) {
                if (v[c.up] > v[c.down]) swap(v[c.up], v[c.down]);
            }
            for (int i = 1; i < n; ++i) {
                if (v[i - 1] > v[i]) {
                    reliable = false;
                    break;
                }
            }
            if (!reliable) break;
        }

        cout << (reliable ? REL : NOT) << '\n';
    }
    return 0;
}
