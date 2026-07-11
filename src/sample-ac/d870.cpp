#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct BigNum {
    string s;
    BigNum() : s("0") {}
    BigNum(const string& t) {
        size_t i = 0;
        while (i + 1 < t.size() && t[i] == '0') i++;
        s = t.substr(i);
    }
    bool operator<(const BigNum& o) const {
        if (s.size() != o.s.size()) return s.size() < o.s.size();
        return s < o.s;
    }
};

BigNum multiply(const BigNum& a, const BigNum& b) {
    const string& A = a.s;
    const string& B = b.s;
    int n = (int)A.size(), m = (int)B.size();
    vector<int> res(n + m, 0);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            res[i + j + 1] += (A[i] - '0') * (B[j] - '0');
        }
    }
    for (int i = n + m - 1; i > 0; i--) {
        res[i - 1] += res[i] / 10;
        res[i] %= 10;
    }
    string r;
    r.reserve(n + m);
    for (int x : res) r += char('0' + x);
    return BigNum(r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    while (cin >> N >> K) {
        string s;
        cin >> s;
        vector<vector<BigNum>> seg(N, vector<BigNum>(N));
        for (int a = 0; a < N; a++) {
            seg[a][a] = BigNum(string(1, s[a]));
            for (int b = a + 1; b < N; b++) {
                seg[a][b] = BigNum(s.substr(a, b - a + 1));
            }
        }
        vector<vector<BigNum>> dp(N + 1, vector<BigNum>(K + 1));
        for (int i = 1; i <= N; i++) {
            dp[i][0] = seg[0][i - 1];
        }
        for (int k = 1; k <= K; k++) {
            for (int i = k + 1; i <= N; i++) {
                BigNum best;
                bool init = false;
                for (int j = k; j < i; j++) {
                    BigNum prod = multiply(dp[j][k - 1], seg[j][i - 1]);
                    if (!init || best < prod) {
                        best = prod;
                        init = true;
                    }
                }
                dp[i][k] = best;
            }
        }
        cout << dp[N][K].s << "\n";
    }
    return 0;
}
