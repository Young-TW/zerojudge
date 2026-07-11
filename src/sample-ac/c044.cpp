#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        cin.ignore();
        vector<int> count(26, 0);
        for (int i = 0; i < n; ++i) {
            string line;
            if (!getline(cin, line)) break;
            for (char c : line) {
                if (isalpha((unsigned char)c)) {
                    count[toupper((unsigned char)c) - 'A']++;
                }
            }
        }

        vector<pair<int, char>> res;
        for (int i = 0; i < 26; ++i) {
            if (count[i] > 0) {
                res.push_back({count[i], 'A' + i});
            }
        }

        sort(res.begin(), res.end(), [](const pair<int, char>& a, const pair<int, char>& b) {
            if (a.first != b.first) {
                return a.first > b.first;
            }
            return a.second < b.second;
        });

        for (const auto& p : res) {
            cout << p.second << " " << p.first << "\n";
        }
    }

    return 0;
}
