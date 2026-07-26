#include <bits/stdc++.h>
using namespace std;

const uint32_t BASE = 1000000000U;          // 1e9

struct BigInt {
    vector<uint32_t> d;                     // little‑endian digits

    BigInt() {}
    explicit BigInt(uint64_t v) {           // construct from small integer
        if (v == 0) return;
        while (v) {
            d.push_back(static_cast<uint32_t>(v % BASE));
            v /= BASE;
        }
    }

    // add other to *this
    void add(const BigInt& other) {
        size_t n = max(d.size(), other.d.size());
        d.resize(n, 0);
        uint64_t carry = 0;
        for (size_t i = 0; i < n; ++i) {
            uint64_t sum = carry + d[i];
            if (i < other.d.size()) sum += other.d[i];
            d[i] = static_cast<uint32_t>(sum % BASE);
            carry = sum / BASE;
        }
        if (carry) d.push_back(static_cast<uint32_t>(carry));
    }

    // operator +=
    BigInt& operator+=(const BigInt& other) {
        add(other);
        return *this;
    }

    string toString() const {
        if (d.empty()) return "0";
        string s = to_string(d.back());
        char buf[10];
        for (int i = static_cast<int>(d.size()) - 2; i >= 0; --i) {
            // pad with leading zeros to width 9
            snprintf(buf, sizeof(buf), "%09u", d[i]);
            s += buf;
        }
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> queries;
    int T;
    if (!(cin >> T)) return 0;
    queries.reserve(T);
    int Nmax = 0;
    for (int i = 0; i < T; ++i) {
        int N; cin >> N;
        queries.push_back(N);
        if (N > Nmax) Nmax = N;
    }

    // DP array
    vector<BigInt> dp(Nmax + 1);
    dp[0] = BigInt(1);                       // one way to obtain sum 0

    for (int j = 1; j * j <= Nmax; ++j) {
        int sq = j * j;
        for (int i = sq; i <= Nmax; ++i) {
            dp[i] += dp[i - sq];
        }
    }

    for (int n : queries) {
        cout << dp[n].toString() << '\n';
    }
    return 0;
}
