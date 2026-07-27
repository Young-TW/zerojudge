#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

// ceiling of a / b  (both positive)
static inline int64 ceil_div(int64 a, int64 b) {
    return (a + b - 1) / b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long m1, m2;
    if (!(cin >> N)) return 0;
    cin >> m1 >> m2;
    vector<long long> S(N);
    for (int i = 0; i < N; ++i) cin >> S[i];

    // factorise m1
    vector<pair<int, int64>> need;          // (prime, required exponent)
    long long x = m1;
    for (int p = 2; (int64)p * p <= x; ++p) {
        if (x % p == 0) {
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                ++cnt;
            }
            need.emplace_back(p, (int64)cnt * m2);
        }
    }
    if (x > 1) {
        need.emplace_back((int)x, (int64)1 * m2);
    }

    // special case M = 1
    if (need.empty()) {
        cout << 0 << "\n";
        return 0;
    }

    const int64 INF = (1LL << 60);
    int64 answer = INF;

    for (int i = 0; i < N; ++i) {
        long long cur = S[i];
        bool ok = true;
        int64 t_i = 0;
        for (auto &pr : need) {
            int p = pr.first;
            int64 needExp = pr.second;
            int64 cnt = 0;
            while (cur % p == 0) {
                cur /= p;
                ++cnt;
            }
            if (cnt == 0) {
                ok = false;
                break;
            }
            int64 needT = ceil_div(needExp, cnt);
            if (needT > t_i) t_i = needT;
        }
        if (ok && t_i < answer) answer = t_i;
    }

    if (answer == INF) cout << -1 << "\n";
    else               cout << answer << "\n";

    return 0;
}
