#include <bits/stdc++.h>
using namespace std;

const uint32_t BASE = 1000000000U;          // 1e9

struct BigInt {
    vector<uint32_t> d;                     // little‑endian limbs

    BigInt(uint64_t v = 0) { *this = v; }

    BigInt& operator=(uint64_t v) {
        d.clear();
        if (v == 0) return *this;
        while (v) {
            d.push_back(static_cast<uint32_t>(v % BASE));
            v /= BASE;
        }
        return *this;
    }

    // add other to this
    void add(const BigInt& other) {
        uint64_t carry = 0;
        size_t n = max(d.size(), other.d.size());
        if (d.size() < n) d.resize(n, 0);
        for (size_t i = 0; i < n; ++i) {
            uint64_t sum = carry + d[i];
            if (i < other.d.size()) sum += other.d[i];
            d[i] = static_cast<uint32_t>(sum % BASE);
            carry = sum / BASE;
        }
        if (carry) d.push_back(static_cast<uint32_t>(carry));
    }

    // multiply by small integer m (here m = 4)
    void mul_small(uint32_t m) {
        if (m == 0 || d.empty()) { d.clear(); return; }
        uint64_t carry = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            uint64_t prod = static_cast<uint64_t>(d[i]) * m + carry;
            d[i] = static_cast<uint32_t>(prod % BASE);
            carry = prod / BASE;
        }
        while (carry) {
            d.push_back(static_cast<uint32_t>(carry % BASE));
            carry /= BASE;
        }
    }

    string toString() const {
        if (d.empty()) return "0";
        stringstream ss;
        int i = static_cast<int>(d.size()) - 1;
        ss << d[i];
        char buf[10];
        for (--i; i >= 0; --i) {
            snprintf(buf, sizeof(buf), "%09u", d[i]);
            ss << buf;
        }
        return ss.str();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    while (cin >> N) {
        BigInt sum(0), power(1);          // power = 4^0
        for (long long i = 0; i < N; ++i) {
            sum.add(power);
            power.mul_small(4);
        }
        cout << sum.toString() << '\n';
    }
    return 0;
}
