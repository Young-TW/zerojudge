#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2, s3;
    while (cin >> s1 >> s2 >> s3) {
        int n = (int)s1.size();               // all three have the same length
        // memo[pos][carry] : -1 unknown, 0 false, 1 true
        vector<array<int, 2>> memo(n + 1);
        for (auto &a : memo) a.fill(-1);

        function<int(int,int)> dfs = [&](int pos, int carry) -> int {
            if (pos == n) return carry == 0;
            int &res = memo[pos][carry];
            if (res != -1) return res;
            res = 0;
            char chA = s1[n - 1 - pos];
            char chB = s2[n - 1 - pos];
            char chC = s3[n - 1 - pos];
            for (int da = 0; da <= 9; ++da) {
                if (chA != '?' && da != chA - '0') continue;
                for (int db = 0; db <= 9; ++db) {
                    if (chB != '?' && db != chB - '0') continue;
                    int sum = da + db + carry;
                    int dc = sum % 10;
                    int ncarry = sum / 10;
                    if (chC != '?' && dc != chC - '0') continue;
                    if (dfs(pos + 1, ncarry)) {
                        res = 1;
                        return res;
                    }
                }
            }
            return res;
        };

        dfs(0, 0);   // fill memo

        string ans1 = s1, ans2 = s2, ans3 = s3;
        int carry = 0;
        for (int pos = 0; pos < n; ++pos) {
            char chA = s1[n - 1 - pos];
            char chB = s2[n - 1 - pos];
            char chC = s3[n - 1 - pos];
            bool found = false;
            for (int da = 0; da <= 9 && !found; ++da) {
                if (chA != '?' && da != chA - '0') continue;
                for (int db = 0; db <= 9 && !found; ++db) {
                    if (chB != '?' && db != chB - '0') continue;
                    int sum = da + db + carry;
                    int dc = sum % 10;
                    int ncarry = sum / 10;
                    if (chC != '?' && dc != chC - '0') continue;
                    if (dfs(pos + 1, ncarry)) {
                        ans1[n - 1 - pos] = char('0' + da);
                        ans2[n - 1 - pos] = char('0' + db);
                        ans3[n - 1 - pos] = char('0' + dc);
                        carry = ncarry;
                        found = true;
                    }
                }
            }
        }

        cout << ans1 << '\n' << ans2 << '\n' << ans3 << '\n';
    }
    return 0;
}
