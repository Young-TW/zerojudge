#include <bits/stdc++.h>
using namespace std;

using u128 = unsigned __int128;

const int MAXLEN = 30;                 // enough for all test data
u128 fact[MAXLEN + 1];

// number of permutations of 'rem' positions with given counters
u128 permCount(const int cnt[10], int rem) {
    u128 res = fact[rem];
    for (int d = 0; d < 10; ++d) {
        res /= fact[cnt[d]];
    }
    return res;
}

// total valid permutations (no leading zero, except length==1)
u128 totalValidPerm(const int cntOrig[10], int len) {
    if (len == 1) return 1;            // the single digit (may be zero)
    u128 total = 0;
    int cnt[10];
    for (int d = 1; d <= 9; ++d) {
        if (cntOrig[d] == 0) continue;
        memcpy(cnt, cntOrig, sizeof(cnt));
        cnt[d]--;
        total += permCount(cnt, len - 1);
    }
    return total;
}

// k-th smallest valid permutation (1‑based)
string kthValid(int cntOrig[10], int len, u128 k) {
    int cnt[10];
    memcpy(cnt, cntOrig, sizeof(cnt));
    string ans;
    ans.reserve(len);
    for (int pos = 0; pos < len; ++pos) {
        int startDigit = (pos == 0 && len > 1) ? 1 : 0;
        for (int d = startDigit; d <= 9; ++d) {
            if (cnt[d] == 0) continue;
            cnt[d]--;
            u128 c = permCount(cnt, len - pos - 1);
            if (k > c) {
                k -= c;
                cnt[d]++;               // restore
            } else {
                ans.push_back(char('0' + d));
                break;
            }
        }
    }
    return ans;
}

// convert unsigned __int128 to decimal string
string u128ToString(u128 x) {
    if (x == 0) return "0";
    string s;
    while (x > 0) {
        int digit = int(x % 10);
        s.push_back('0' + digit);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    // factorials
    fact[0] = 1;
    for (int i = 1; i <= MAXLEN; ++i) fact[i] = fact[i - 1] * (u128)i;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        string n;
        unsigned long long h_input;
        char s;
        cin >> n >> h_input >> s;

        int cnt[10] = {0};
        for (char c : n) cnt[c - '0']++;

        int len = (int)n.size();

        u128 total = totalValidPerm(cnt, len);
        u128 k;
        if (s == 's') {
            k = (u128)h_input;                 // h‑th smallest
        } else { // 'b'
            k = total - (u128)h_input + 1;     // h‑th largest → (tot‑h+1)-th smallest
        }

        string result = kthValid(cnt, len, k);
        cout << result << '\n';
    }
    return 0;
}
