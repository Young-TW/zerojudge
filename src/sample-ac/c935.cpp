#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

using namespace std;

class BigInt {
public:
    static const uint32_t BASE = 1000000000;
    vector<uint32_t> d; // little-endian

    BigInt() : d(1, 0) {}
    BigInt(uint64_t v) {
        if (v == 0) d.push_back(0);
        else {
            while (v) {
                d.push_back(v % BASE);
                v /= BASE;
            }
        }
    }
    BigInt(const string& s) {
        for (int i = (int)s.size(); i > 0; i -= 9) {
            int start = max(0, i - 9);
            int len = i - start;
            d.push_back(stoul(s.substr(start, len)));
        }
        normalize();
    }

    void normalize() {
        while (d.size() > 1 && d.back() == 0) d.pop_back();
    }

    bool isZero() const { return d.size() == 1 && d[0] == 0; }
    bool isEven() const { return (d[0] & 1) == 0; }
    bool isOdd() const { return (d[0] & 1) != 0; }

    int cmp(const BigInt& other) const {
        if (d.size() != other.d.size()) return d.size() < other.d.size() ? -1 : 1;
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            if (d[i] != other.d[i]) return d[i] < other.d[i] ? -1 : 1;
        }
        return 0;
    }

    bool operator==(const BigInt& other) const { return cmp(other) == 0; }
    bool operator!=(const BigInt& other) const { return cmp(other) != 0; }
    bool operator<(const BigInt& other) const { return cmp(other) < 0; }
    bool operator<=(const BigInt& other) const { return cmp(other) <= 0; }
    bool operator>(const BigInt& other) const { return cmp(other) > 0; }
    bool operator>=(const BigInt& other) const { return cmp(other) >= 0; }

    BigInt operator+(const BigInt& other) const {
        BigInt res;
        res.d.resize(max(d.size(), other.d.size()) + 1);
        uint64_t carry = 0;
        for (size_t i = 0; i < res.d.size(); ++i) {
            uint64_t sum = carry;
            if (i < d.size()) sum += d[i];
            if (i < other.d.size()) sum += other.d[i];
            res.d[i] = sum % BASE;
            carry = sum / BASE;
        }
        res.normalize();
        return res;
    }

    BigInt operator+(uint32_t v) const {
        BigInt res = *this;
        uint64_t carry = v;
        for (size_t i = 0; i < res.d.size() && carry; ++i) {
            uint64_t sum = res.d[i] + carry;
            res.d[i] = sum % BASE;
            carry = sum / BASE;
        }
        if (carry) res.d.push_back(carry);
        return res;
    }

    BigInt operator-(const BigInt& other) const { // assumes *this >= other
        BigInt res;
        res.d.resize(d.size());
        int64_t carry = 0;
        for (size_t i = 0; i < d.size(); ++i) {
            int64_t diff = (int64_t)d[i] - carry;
            if (i < other.d.size()) diff -= other.d[i];
            if (diff < 0) {
                diff += BASE;
                carry = 1;
            } else carry = 0;
            res.d[i] = diff;
        }
        res.normalize();
        return res;
    }

    BigInt operator-(uint32_t v) const { // assumes *this >= v
        BigInt res = *this;
        int64_t borrow = v;
        for (size_t i = 0; i < res.d.size() && borrow; ++i) {
            int64_t diff = (int64_t)res.d[i] - borrow;
            if (diff < 0) {
                diff += BASE;
                borrow = 1;
            } else borrow = 0;
            res.d[i] = diff;
        }
        res.normalize();
        return res;
    }

    BigInt operator*(const BigInt& other) const {
        if (isZero() || other.isZero()) return BigInt(0);
        BigInt res;
        res.d.resize(d.size() + other.d.size());
        for (size_t i = 0; i < d.size(); ++i) {
            uint64_t carry = 0;
            for (size_t j = 0; j < other.d.size() || carry; ++j) {
                uint64_t cur = res.d[i + j] + carry;
                if (j < other.d.size()) cur += (uint64_t)d[i] * other.d[j];
                res.d[i + j] = cur % BASE;
                carry = cur / BASE;
            }
        }
        res.normalize();
        return res;
    }

    void div2() { // divide by 2 in place
        uint64_t carry = 0;
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            uint64_t cur = d[i] + carry * BASE;
            d[i] = cur / 2;
            carry = cur % 2;
        }
        normalize();
    }

    uint32_t mod_small(uint32_t m) const {
        uint64_t rem = 0;
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            rem = (rem * BASE + d[i]) % m;
        }
        return rem;
    }

    string toString() const {
        if (isZero()) return "0";
        string res = to_string(d.back());
        char buf[16];
        for (int i = (int)d.size() - 2; i >= 0; --i) {
            snprintf(buf, sizeof(buf), "%09u", d[i]);
            res += buf;
        }
        return res;
    }
};

BigInt add_mod(const BigInt& a, const BigInt& b, const BigInt& mod) {
    BigInt res = a + b;
    if (res >= mod) res = res - mod;
    return res;
}

BigInt sub_mod(const BigInt& a, const BigInt& b, const BigInt& mod) {
    if (a >= b) return a - b;
    else return a + mod - b;
}

BigInt mul_mod(const BigInt& a, const BigInt& b, const BigInt& mod) {
    BigInt res = 0;
    BigInt x = a;
    BigInt y = b;
    while (!y.isZero()) {
        if (y.isOdd()) res = add_mod(res, x, mod);
        x = add_mod(x, x, mod);
        y.div2();
    }
    return res;
}

BigInt pow_mod(BigInt a, BigInt e, const BigInt& mod) {
    BigInt res = 1;
    while (!e.isZero()) {
        if (e.isOdd()) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        e.div2();
    }
    return res;
}

BigInt gcd(BigInt a, BigInt b) {
    if (a.isZero()) return b;
    if (b.isZero()) return a;
    int shift = 0;
    while (a.isEven() && b.isEven()) {
        a.div2();
        b.div2();
        shift++;
    }
    while (!a.isZero()) {
        while (a.isEven()) a.div2();
        while (b.isEven()) b.div2();
        if (a >= b) {
            a = a - b;
            a.div2();
        } else {
            b = b - a;
            b.div2();
        }
    }
    while (shift--) b = b + b;
    return b;
}

bool isPrime(BigInt n) {
    if (n < 2) return false;
    static const int smallPrimes[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (int p : smallPrimes) {
        if (n == BigInt(p)) return true;
        if (n.mod_small(p) == 0) return false;
    }
    BigInt d = n - 1;
    int s = 0;
    while (d.isEven()) {
        d.div2();
        s++;
    }
    for (int a : smallPrimes) {
        if (BigInt(a) >= n) break;
        BigInt x = pow_mod(BigInt(a), d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

BigInt pollards_rho(BigInt n) {
    if (n.isEven()) return BigInt(2);
    for (int c = 1; ; c++) {
        BigInt x = 2;
        BigInt y = 2;
        BigInt d = 1;
        BigInt C = c;
        while (d == 1) {
            x = add_mod(mul_mod(x, x, n), C, n);
            y = add_mod(mul_mod(y, y, n), C, n);
            y = add_mod(mul_mod(y, y, n), C, n);
            BigInt diff = (x >= y) ? x - y : y - x;
            d = gcd(diff, n);
        }
        if (d != n) return d;
    }
}

BigInt divide_exact(BigInt n, BigInt d) {
    BigInt low = 1;
    BigInt high = n;
    while (low <= high) {
        BigInt mid = low + high;
        mid.div2();
        BigInt prod = d * mid;
        if (prod == n) return mid;
        else if (prod < n) low = mid + 1;
        else high = mid - 1;
    }
    return BigInt(0); // should not happen
}

void factor(BigInt n, vector<BigInt>& factors) {
    if (n == 1) return;
    if (isPrime(n)) {
        factors.push_back(n);
        return;
    }
    BigInt d = pollards_rho(n);
    BigInt q = divide_exact(n, d);
    factor(d, factors);
    factor(q, factors);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        BigInt n(s);
        vector<BigInt> factors;
        factor(n, factors);
        sort(factors.begin(), factors.end(), [](const BigInt& a, const BigInt& b) {
            return a < b;
        });
        for (size_t i = 0; i < factors.size(); ++i) {
            if (i) cout << ' ';
            cout << factors[i].toString();
        }
        cout << '\n';
    }
    return 0;
}
