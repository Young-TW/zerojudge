#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(2);

    string line;
    while (std::getline(cin, line)) {
        // Remove possible carriage return (for Windows line endings)
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        int cnt[26] = {0};
        int total = 0;

        for (char ch : line) {
            if (ch >= 'a' && ch <= 'z') {
                cnt[ch - 'a']++;
                ++total;
            } else if (ch >= 'A' && ch <= 'Z') {
                cnt[ch - 'A']++;
                ++total;
            }
        }

        // first line: counts
        for (int i = 0; i < 26; ++i) {
            if (i) cout << ' ';
            cout << cnt[i];
        }
        cout << '\n';

        // second line: percentages
        for (int i = 0; i < 26; ++i) {
            if (i) cout << ' ';
            double pct = (total == 0) ? 0.0 : (static_cast<double>(cnt[i]) * 100.0 / total);
            cout << pct;
        }
        cout << '\n';
    }
    return 0;
}
