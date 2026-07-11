#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int manacher(const string& s) {
    if (s.empty()) return 0;
    string t = "^#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    t += '$';
    
    int n = t.size();
    vector<int> p(n, 0);
    int C = 0, R = 0;
    for (int i = 1; i < n - 1; ++i) {
        int mirr = 2 * C - i;
        if (R > i) {
            p[i] = min(R - i, p[mirr]);
        }
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
            p[i]++;
        }
        if (i + p[i] > R) {
            C = i;
            R = i + p[i];
        }
    }
    int max_len = 0;
    for (int i = 0; i < n; ++i) {
        max_len = max(max_len, p[i]);
    }
    return max_len;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string token;
    if (cin >> token) {
        bool is_num = true;
        for (char c : token) {
            if (c < '0' || c > '9') {
                is_num = false;
                break;
            }
        }
        if (is_num) {
            int T = 0;
            for (char c : token) T = T * 10 + (c - '0');
            while (T--) {
                string s;
                cin >> s;
                cout << manacher(s) << "\n";
            }
        } else {
            cout << manacher(token) << "\n";
            string s;
            while (cin >> s) {
                cout << manacher(s) << "\n";
            }
        }
    }
    return 0;
}
