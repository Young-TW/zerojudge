#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    int n, m;
    while (cin >> n >> m) {
        string text, origin, after;
        cin >> text >> origin >> after;   // lengths: n, m, m

        // mapping table: for every ASCII code store its current image
        char mp[128];
        for (int i = 0; i < 128; ++i) mp[i] = static_cast<char>(i);
        for (char c : charset) mp[static_cast<int>(c)] = c;   // identity for needed chars

        // apply the m replacement rules
        for (int i = 0; i < m; ++i) {
            char a = origin[i];
            char b = after[i];
            for (char c : charset) {
                if (mp[static_cast<int>(c)] == a)
                    mp[static_cast<int>(c)] = b;
            }
        }

        // encrypt the text
        string result;
        result.reserve(n);
        for (char ch : text) {
            result.push_back(mp[static_cast<int>(ch)]);
        }

        cout << result << '\n';
    }
    return 0;
}
