#include <bits/stdc++.h>
using namespace std;

/* ---------- big integer, base 1e9 ---------- */
struct BigInt {
    static const uint32_t BASE = 1000000000U;          // 1e9
    vector<uint32_t> d;                               // little endian

    BigInt(uint64_t v = 0) { *this = v; }

    BigInt& operator = (uint64_t v) {
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

    // multiply by small integer (fits in 32 bits, but we accept 64)
    void mul(uint64_t m) {
        if (m == 0 || isZero()) { d.clear(); return; }
        uint64_t carry = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            uint64_t cur = (uint64_t)d[i] * m + carry;
            d[i] = (uint32_t)(cur % BASE);
            carry = cur / BASE;
        }
        while (carry) {
            d.push_back((uint32_t)(carry % BASE));
            carry /= BASE;
        }
    }

    string toString() const {
        if (d.empty()) return "0";
        string s = to_string(d.back());
        char buf[10];
        for (int i = (int)d.size() - 2; i >= 0; --i) {
            snprintf(buf, sizeof(buf), "%09u", d[i]);
            s += buf;
        }
        return s;
    }
};

/* ---------- prime sieve up to 200000 ---------- */
vector<int> primes;
void sieve(int limit = 200000) {
    vector<bool> is(limit + 1, true);
    is[0] = is[1] = false;
    for (int i = 2; i * i <= limit; ++i) if (is[i]) {
        for (int j = i * i; j <= limit; j += i) is[j] = false;
    }
    for (int i = 2; i <= limit; ++i) if (is[i]) primes.push_back(i);
}

/* factorise a positive integer (<= 200000) and update map */
void add_factor(int x, unordered_map<int,long long> &mp, int sign) {
    int tmp = x;
    for (int p : primes) {
        if ((long long)p * p > tmp) break;
        if (tmp % p == 0) {
            long long cnt = 0;
            while (tmp % p == 0) {
                tmp /= p;
                ++cnt;
            }
            mp[p] += sign * cnt;
        }
    }
    if (tmp > 1) mp[tmp] += sign;          // remaining prime
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();

    int t, n, d;
    while (cin >> t >> n >> d) {
        vector<int> a(t + 1);
        long long A = 0;
        for (int i = 1; i <= t; ++i) {
            cin >> a[i];
            A += a[i];
        }

        vector<int> x(n), y(n);
        for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];   // x is ignored

        vector<int> cnt(t + 1, 0);
        unordered_map<int,long long> expo;   // prime -> exponent (num - den)

        for (int k = 0; k < n; ++k) {
            int col = y[k];
            long long num = a[col] + (long long)d * cnt[col];
            long long den = A + (long long)d * k;   // k = (k-th draw) - 1

            add_factor((int)num, expo, +1);
            add_factor((int)den, expo, -1);

            ++cnt[col];
        }

        BigInt num(1), den(1);
        for (auto &kv : expo) {
            int p = kv.first;
            long long e = kv.second;
            if (e > 0) {
                for (long long i = 0; i < e; ++i) num.mul(p);
            } else if (e < 0) {
                for (long long i = 0; i < -e; ++i) den.mul(p);
            }
        }

        cout << num.toString() << '/' << den.toString() << '\n';
    }
    return 0;
}
