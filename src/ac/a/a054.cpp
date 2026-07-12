#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    int d[11];
    for (int i = 0; i < 9; i++) d[i + 2] = s[i] - '0';
    int d10 = s[8] - '0';
    int base = 0;
    int w[9] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    for (int i = 2; i <= 9; i++) base += d[i] * w[i - 2];
    (void)d10;

    vector<pair<char, int>> mp = {
        {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14},
        {'F', 15}, {'G', 16}, {'H', 17}, {'I', 34}, {'J', 18},
        {'K', 19}, {'L', 20}, {'M', 21}, {'N', 22}, {'O', 35},
        {'P', 23}, {'Q', 24}, {'R', 25}, {'S', 26}, {'T', 27},
        {'U', 28}, {'V', 29}, {'W', 32}, {'X', 30}, {'Y', 31},
        {'Z', 33}
    };
    int target = (10 - d10) % 10;
    string ans;
    for (auto [c, v] : mp) {
        int x = v / 10, y = v % 10;
        int s = x + 9 * y + base;
        if ((s % 10 + 10) % 10 == target) ans.push_back(c);
    }
    cout << ans << "\n";
    return 0;
}
