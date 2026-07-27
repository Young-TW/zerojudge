#include <bits/stdc++.h>
using namespace std;

/* ---------- simple big integer (base 1e9) ---------- */
struct BigInt {
    static const uint32_t BASE = 1000000000U;
    vector<uint32_t> d;               // little endian, d[0] least significant

    BigInt() { d.clear(); }
    BigInt(uint64_t v) { *this = v; }

    BigInt& operator=(uint64_t v) {
        d.clear();
        if (v == 0) return *this;
        while (v) {
            d.push_back(v % BASE);
            v /= BASE;
        }
        return *this;
    }

    bool isZero() const { return d.empty(); }

    void trim() {
        while (!d.empty() && d.back() == 0) d.pop_back();
    }

    /* addition */
    BigInt& operator+=(const BigInt& other) {
        uint64_t carry = 0;
        size_t n = max(d.size(), other.d.size());
        if (d.size() < n) d.resize(n, 0);
        for (size_t i = 0; i < n; ++i) {
            uint64_t sum = carry + d[i];
            if (i < other.d.size()) sum += other.d[i];
            d[i] = uint32_t(sum % BASE);
            carry = sum / BASE;
        }
        if (carry) d.push_back(uint32_t(carry));
        return *this;
    }

    friend BigInt operator+(BigInt a, const BigInt& b) {
        a += b;
        return a;
    }

    string toString() const {
        if (d.empty()) return "0";
        stringstream ss;
        int i = (int)d.size() - 1;
        ss << d[i];
        char buf[10];
        for (--i; i >= 0; --i) {
            snprintf(buf, sizeof(buf), "%09u", d[i]);
            ss << buf;
        }
        return ss.str();
    }
};

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        int d;
        if (!(cin >> d)) break;          // should not happen
        vector<bool> broken(n + 1, false);
        for (int i = 0; i < d; ++i) {
            int p; cin >> p;
            if (p >= 0 && p <= n) broken[p] = true;
        }

        vector<BigInt> dp(n + 1);
        dp[0] = BigInt(1);
        for (int i = 1; i <= n; ++i) {
            if (broken[i]) {
                dp[i] = BigInt(0);
                continue;
            }
            BigInt sum(0);
            for (int k = 1; k <= m; ++k) {
                int prev = i - k;
                if (prev < 0) break;
                sum += dp[prev];
            }
            dp[i] = sum;
        }
        cout << dp[n].toString() << '\n';
    }
    return 0;
}
