#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

string div(string num, int t, int &rem) {
    string res;
    rem = 0;
    for (char c : num) {
        int digit = rem * 10 + (c - '0');
        res += (char)('0' + digit / t);
        rem = digit % t;
    }
    int pos = 0;
    while (pos < (int)res.size() - 1 && res[pos] == '0') pos++;
    return res.substr(pos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<string> names(n);
        for (int i = 0; i < n; ++i) {
            cin >> names[i];
        }
        int t;
        cin >> t;
        string ba, c;
        cin >> ba >> c;

        int p = 0;
        while (p < (int)ba.size() && isdigit((unsigned char)ba[p])) p++;
        string b_str = ba.substr(0, p);
        string a = ba.substr(p);

        int idx_a = -1, idx_c = -1;
        for (int i = 0; i < n; ++i) {
            if (names[i] == a) idx_a = i;
            if (names[i] == c) idx_c = i;
        }

        string current_str = b_str;
        vector<int> rem(n, 0);

        for (int i = idx_a; i < idx_c; ++i) {
            int r;
            current_str = div(current_str, t, r);
            rem[i] = r;
        }

        if (current_str == "0") {
            cout << -1 << "\n";
        } else {
            cout << current_str << c;
            for (int i = idx_a; i < idx_c; ++i) {
                if (rem[i] > 0) {
                    cout << " " << rem[i] << names[i];
                }
            }
            cout << "\n";
        }
    }
    return 0;
}
