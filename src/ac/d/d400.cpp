#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

bool check(const string& s, const vector<pair<char, char>>& rules) {
    for (const auto& rule : rules) {
        char a = rule.first;
        char b = rule.second;
        bool found_a = false;
        for (char c : s) {
            if (c == a) found_a = true;
            if (c == b) {
                if (!found_a) return false;
            }
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int m;
        cin >> m;
        vector<pair<char, char>> rules;
        for (int i = 0; i < m; i++) {
            char a, b;
            cin >> a >> b;
            rules.emplace_back(a, b);
        }

        vector<string> results;
        sort(s.begin(), s.end());
        do {
            if (check(s, rules)) {
                results.push_back(s);
                if (results.size() >= 10) break;
            }
        } while (next_permutation(s.begin(), s.end()));

        if (results.empty()) {
            cout << "NANJ你唬我" << endl;
        } else {
            for (const string& res : results) {
                cout << res << endl;
            }
        }
    }
    return 0;
}
