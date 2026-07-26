#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <cstdio>

class BigInt {
public:
    static const uint32_t BASE = 1000000000U;          // 10^9
    std::vector<uint32_t> d;                          // little‑endian

    BigInt() : d(1, 0) {}
    explicit BigInt(uint64_t v) { *this = v; }

    BigInt& operator=(uint64_t v) {
        d.clear();
        if (v == 0) d.push_back(0);
        else {
            while (v) {
                d.push_back(static_cast<uint32_t>(v % BASE));
                v /= BASE;
            }
        }
        return *this;
    }

    // multiply by a small (fits into 64 bits) integer
    void mul(uint64_t m) {
        if (m == 0) { d.assign(1, 0); return; }
        uint64_t carry = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            uint64_t cur = static_cast<uint64_t>(d[i]) * m + carry;
            d[i] = static_cast<uint32_t>(cur % BASE);
            carry = cur / BASE;
        }
        while (carry) {
            d.push_back(static_cast<uint32_t>(carry % BASE));
            carry /= BASE;
        }
    }

    bool operator<(const BigInt& other) const {
        if (d.size() != other.d.size())
            return d.size() < other.d.size();
        for (int i = static_cast<int>(d.size()) - 1; i >= 0; --i) {
            if (d[i] != other.d[i])
                return d[i] < other.d[i];
        }
        return false; // equal
    }

    std::string toString() const {
        std::ostringstream oss;
        int n = static_cast<int>(d.size());
        oss << d.back();
        char buf[12];
        for (int i = n - 2; i >= 0; --i) {
            std::snprintf(buf, sizeof(buf), "%09u", d[i]);
            oss << buf;
        }
        return oss.str();
    }
};

// recursive generation of divisors
void genDivisors(int idx,
                 const std::vector<std::pair<uint64_t, int>>& fac,
                 const BigInt& cur,
                 std::vector<BigInt>& out)
{
    if (idx == static_cast<int>(fac.size())) {
        out.push_back(cur);
        return;
    }
    uint64_t p = fac[idx].first;
    int k = fac[idx].second;
    BigInt val = cur;
    for (int e = 0; e <= k; ++e) {
        genDivisors(idx + 1, fac, val, out);
        if (e < k) val.mul(p);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    if (!(std::cin >> T)) return 0;
    std::string dummy;
    std::getline(std::cin, dummy);          // consume end of line after T

    for (int tc = 0; tc < T; ++tc) {
        std::string line;
        // read a non‑empty line (skip possible blank lines)
        while (std::getline(std::cin, line)) {
            if (!line.empty()) break;
        }
        std::istringstream iss(line);
        std::vector<std::pair<uint64_t, int>> fac;
        uint64_t p; int k;
        while (iss >> p >> k) fac.emplace_back(p, k);

        // compute N
        BigInt N(1);
        for (const auto& pr : fac) {
            for (int i = 0; i < pr.second; ++i) N.mul(pr.first);
        }

        // generate all divisors
        std::vector<BigInt> divisors;
        genDivisors(0, fac, BigInt(1), divisors);
        std::sort(divisors.begin(), divisors.end());

        // output
        std::cout << N.toString() << " :";
        for (const auto& d : divisors) {
            std::cout << ' ' << d.toString();
        }
        if (tc + 1 != T) std::cout << '\n';
    }
    return 0;
}
