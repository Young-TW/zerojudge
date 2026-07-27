#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

/* ---------- h(y) ---------- */
int64 H(int y) {
    if (y < 2) return -1;
    int r = y % 6;
    if (r == 0 || r == 1) return -1;
    if (r == 2 || r == 5) return 2;
    return 5;                     // r == 3 or 4
}

/* ---------- g(z) ---------- */
int64 G(int z) {
    if (z <= 2) {
        int64 zz = 1LL * z * z;
        return zz - 1;
    }
    return 2;
}

/* ---------- sum_{k=6}^{x} h(k) ,  x >= 6 ---------- */
int64 sumH(int x) {
    // prefix of one period (starting with k = 6)
    static const int64 pref[7] = {0, -1, -2, 0, 5, 10, 12};
    int64 n = static_cast<int64>(x) - 5;   // number of terms
    int64 full = n / 6;
    int rem = static_cast<int>(n % 6);
    return full * 12 + pref[rem];
}

/* ---------- memoised f(x) ---------- */
unordered_map<int, int64> memo;

int64 F(int x) {
    auto it = memo.find(x);
    if (it != memo.end()) return it->second;

    int64 ans;
    if (x > 5) {
        ans = -3 - sumH(x);
    } else {
        int64 hx = H(x);
        if (x == hx) {
            ans = 1;
        } else if (x > hx) {
            ans = F(x - 1) - hx;
        } else {                // x < hx
            int64 gx = G(x);
            ans = F(static_cast<int>(gx)) - gx;
        }
    }
    memo[x] = ans;
    return ans;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x;
    while (cin >> x) {
        cout << F(x) << '\n';
    }
    return 0;
}
