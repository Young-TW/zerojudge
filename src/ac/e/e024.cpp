#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;

const int BASE = 1000;          // 10³
const int BASE_DIGS = 3;
const double PI = acos(-1.0);

/* ---------- FFT ---------- */
void fft(vector<cd>& a, bool invert) {
        int n = (int)a.size();
        for (int i = 1, j = 0; i < n; ++i) {
                int bit = n >> 1;
                for (; j & bit; bit >>= 1) j ^= bit;
                j ^= bit;
                if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
                double ang = 2 * PI / len * (invert ? -1 : 1);
                cd wlen(cos(ang), sin(ang));
                for (int i = 0; i < n; i += len) {
                        cd w(1);
                        for (int j = 0; j < len / 2; ++j) {
                                cd u = a[i + j];
                                cd v = a[i + j + len / 2] * w;
                                a[i + j] = u + v;
                                a[i + j + len / 2] = u - v;
                                w *= wlen;
                        }
                }
        }
        if (invert) {
                for (cd& x : a) x /= n;
        }
}

/* ---------- Big Integer ---------- */
struct BigInt {
        vector<int> a;                 // little endian, base = BASE

        BigInt() {}
        BigInt(long long v) { *this = v; }

        BigInt& operator = (long long v) {
                a.clear();
                if (v == 0) return *this;
                while (v) {
                        a.push_back(int(v % BASE));
                        v /= BASE;
                }
                return *this;
        }

        bool isZero() const { return a.empty(); }
};

/* ---------- Multiplication ---------- */
BigInt multiply(const BigInt& x, const BigInt& y) {
        if (x.isZero() || y.isZero()) return BigInt(0);

        const vector<int>& a = x.a;
        const vector<int>& b = y.a;
        int n1 = (int)a.size(), n2 = (int)b.size();

        int n = 1;
        while (n < n1 + n2) n <<= 1;

        vector<cd> fa(n), fb(n);
        for (int i = 0; i < n1; ++i) fa[i] = cd(a[i], 0);
        for (int i = 0; i < n2; ++i) fb[i] = cd(b[i], 0);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; ++i) fa[i] *= fb[i];
        fft(fa, true);

        BigInt res;
        res.a.resize(n);
        long long carry = 0;
        for (int i = 0; i < n; ++i) {
                long long cur = (long long)(fa[i].real() + 0.5) + carry;
                res.a[i] = int(cur % BASE);
                carry = cur / BASE;
        }
        while (carry) {
                res.a.push_back(int(carry % BASE));
                carry /= BASE;
        }
        while (!res.a.empty() && res.a.back() == 0) res.a.pop_back();
        return res;
}

/* ---------- Power (binary exponentiation) ---------- */
BigInt power(BigInt base, long long exp) {
        BigInt result(1);
        while (exp > 0) {
                if (exp & 1LL) result = multiply(result, base);
                exp >>= 1LL;
                if (exp) base = multiply(base, base);
        }
        return result;
}

/* ---------- Output ---------- */
void print(const BigInt& v) {
        if (v.isZero()) { cout << "0\n"; return; }
        int n = (int)v.a.size();
        cout << v.a.back();
        for (int i = n - 2; i >= 0; --i)
                cout << setw(BASE_DIGS) << setfill('0') << v.a[i];
        cout << '\n';
}

/* ---------- Main ---------- */
int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        long long n, m;
        while (cin >> n >> m) {
                if (n == 0 && m == 0) break;
                if (n == 1) { cout << "1\n"; continue; }

                BigInt base(n);
                BigInt ans = power(base, m);
                print(ans);
        }
        return 0;
}
