#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct BigInt {
    static const int BASE = 1000000000;
    vector<int> d;  // little-endian
    int sign;       // 1 or -1

    BigInt() : sign(1) {}
    BigInt(long long v) { *this = v; }

    BigInt& operator=(long long v) {
        d.clear();
        if (v < 0) {
            sign = -1;
            v = -v;
        } else {
            sign = 1;
        }
        if (v == 0) return *this;
        while (v > 0) {
            d.push_back(int(v % BASE));
            v /= BASE;
        }
        return *this;
    }

    bool isZero() const { return d.empty(); }

    void normalize() {
        while (!d.empty() && d.back() == 0) d.pop_back();
        if (d.empty()) sign = 1;
    }

    // compare absolute values: -1 if |this| < |other|, 0 if equal, 1 if greater
    int cmp_abs(const BigInt& other) const {
        if (d.size() != other.d.size())
            return d.size() < other.d.size() ? -1 : 1;
        for (int i = (int)d.size() - 1; i >= 0; --i) {
            if (d[i] != other.d[i])
                return d[i] < other.d[i] ? -1 : 1;
        }
        return 0;
    }

    void add_abs(const BigInt& other) {  // this = |this| + |other|
        int n = max(d.size(), other.d.size());
        d.resize(n, 0);
        unsigned long long carry = 0;
        for (int i = 0; i < n; ++i) {
            unsigned long long sum = carry + d[i];
            if (i < (int)other.d.size()) sum += other.d[i];
            d[i] = int(sum % BASE);
            carry = sum / BASE;
        }
        if (carry) d.push_back(int(carry));
    }

    void sub_abs(const BigInt& other) {  // this = |this| - |other|, assumes |this| >= |other|
        long long carry = 0;
        for (int i = 0; i < (int)d.size(); ++i) {
            long long val = (long long)d[i] - carry;
            if (i < (int)other.d.size()) val -= other.d[i];
            if (val < 0) {
                val += BASE;
                carry = 1;
            } else {
                carry = 0;
            }
            d[i] = int(val);
        }
        normalize();
    }

    void add(const BigInt& other) {
        if (sign == other.sign) {
            add_abs(other);
        } else {
            int cmp = cmp_abs(other);
            if (cmp == 0) {
                d.clear();
                sign = 1;
            } else if (cmp > 0) {
                sub_abs(other);
            } else {
                BigInt temp = other;
                temp.sub_abs(*this);
                *this = temp;
            }
        }
    }

    void mul(int m) {  // m >= 0
        if (m == 0 || isZero()) {
            d.clear();
            sign = 1;
            return;
        }
        if (m < 0) {
            sign *= -1;
            m = -m;
        }
        unsigned long long carry = 0;
        for (int i = 0; i < (int)d.size(); ++i) {
            unsigned long long prod = (unsigned long long)d[i] * m + carry;
            d[i] = int(prod % BASE);
            carry = prod / BASE;
        }
        while (carry) {
            d.push_back(int(carry % BASE));
            carry /= BASE;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    bool first_case = true;
    while (cin >> n >> m) {
        vector<long long> a(n + 1);
        for (int i = 0; i <= n; ++i) cin >> a[i];

        if (!first_case) cout << "\n";
        first_case = false;

        // Find first non-zero coefficient
        int k = 0;
        while (k <= n && a[k] == 0) ++k;

        if (k > n) {  // all coefficients are zero
            cout << m << "\n";
            for (int i = 1; i <= m; ++i) cout << i << "\n";
            continue;
        }

        if (k == n) {  // constant non-zero polynomial
            cout << "0\n";
            continue;
        }

        // Reduced polynomial: a[k] + a[k+1] x + ... + a[n] x^{n-k}
        long long constant = a[k];
        long long abs_const = constant >= 0 ? constant : -constant;

        // Find all positive divisors of |constant| that are <= m
        vector<int> candidates;
        for (long long i = 1; i <= abs_const / i; ++i) {
            if (abs_const % i == 0) {
                if (i <= m) candidates.push_back((int)i);
                long long j = abs_const / i;
                if (j != i && j <= m) candidates.push_back((int)j);
            }
        }
        sort(candidates.begin(), candidates.end());

        vector<int> roots;
        for (int d : candidates) {
            BigInt res = a[n];
            for (int i = n - 1; i >= k; --i) {
                res.mul(d);
                res.add(BigInt(a[i]));
            }
            if (res.isZero()) roots.push_back(d);
        }

        cout << roots.size() << "\n";
        for (int r : roots) cout << r << "\n";
    }
    return 0;
}
