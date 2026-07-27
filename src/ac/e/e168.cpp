#include <bits/stdc++.h>
using namespace std;

bool match(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            vector<char> st;                 // stack of opening brackets
            vector<pair<int,int>> groups;     // (left, right) of top‑level groups
            bool ok = true;
            int group_start = -1;             // start index of current top‑level group

            for (int pos = 0; pos < (int)s.size(); ++pos) {
                char c = s[pos];
                if (c == '(' || c == '[' || c == '{') {
                    st.push_back(c);
                    if (st.size() == 1)        // entering a top‑level group
                        group_start = pos;
                } else { // closing bracket
                    if (st.empty() || !match(st.back(), c)) {
                        ok = false;
                        break;
                    }
                    st.pop_back();
                    if (st.empty()) {          // finished a top‑level group
                        groups.emplace_back(group_start, pos);
                        group_start = -1;
                    }
                }
            }
            if (!st.empty()) ok = false;      // unmatched openings

            string answer;
            if (ok) {
                for (auto &g : groups) {
                    int l = g.first, r = g.second;
                    if (r - l == 1) {          // empty inner part
                        ok = false;
                        break;
                    }
                    answer.append(s.substr(l + 1, r - l - 1));
                }
            }

            if (!ok || answer.empty())
                cout << "Product Broken!!\n";
            else
                cout << answer << '\n';
        }
    }
    return 0;
}
