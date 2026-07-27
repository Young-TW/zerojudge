#include <bits/stdc++.h>
using namespace std;

// swap case of letters
string swap_case(const string &s) {
    string r = s;
    for (char &c : r) {
        if ('a' <= c && c <= 'z')
            c = char(c - 'a' + 'A');
        else if ('A' <= c && c <= 'Z')
            c = char(c - 'A' + 'a');
    }
    return r;
}

// delete all (non‑overlapping) occurrences of pat from src
string erase_all(const string &src, const string &pat) {
    if (pat.empty()) return src;          // nothing to erase
    string res;
    size_t i = 0, n = src.size(), m = pat.size();
    while (i < n) {
        if (i + m <= n && src.compare(i, m, pat) == 0) {
            i += m;                       // skip the whole pattern
        } else {
            res.push_back(src[i]);
            ++i;
        }
    }
    return res;
}

// replace all (non‑overlapping) occurrences of pat by rep in src
string replace_all(const string &src, const string &pat, const string &rep) {
    if (pat.empty()) return src;          // nothing to replace
    string res;
    size_t i = 0, n = src.size(), m = pat.size();
    while (i < n) {
        if (i + m <= n && src.compare(i, m, pat) == 0) {
            res += rep;
            i += m;
        } else {
            res.push_back(src[i]);
            ++i;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        int m, n, p;
        if (!(cin >> m >> n >> p)) break;

        string a = s.substr(0, m - 1);          // first part
        string b = s.substr(m - 1);             // second part
        string t;

        if (n == 1) {
            t = swap_case(s) + "Immorta1";
        } else if (n == 2) {
            string tmp = erase_all(s, b);
            t = replace_all(tmp, "1013", "hh4742");
        } else { // n == 3
            int k = abs(n - m);
            int pos = k - 1;                    // 0‑based insertion position
            if (pos < 0) pos = 0;
            if (pos > (int)a.size()) pos = (int)a.size();
            t = a.substr(0, pos) + b + a.substr(pos);
        }

        // repeat each character (p+1) times
        string ans;
        ans.reserve(t.size() * (p + 1));
        for (char c : t) ans.append(p + 1, c);
        cout << ans << '\n';
    }
    return 0;
}
