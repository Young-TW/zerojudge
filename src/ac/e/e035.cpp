#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1.0);
const int BASE = 100;          // two decimal digits

/* -------------------- FFT -------------------- */
void fft(vector<cd> & a, bool invert) {
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
        for (cd & x : a) x /= n;
    }
}

/* -------------- big integer helpers ---------- */
vector<int> str_to_vec(const string &s) {
    vector<int> v;
    for (int i = (int)s.length(); i > 0; i -= 2) {
        int start = max(0, i - 2);
        int len = i - start;
        v.push_back(stoi(s.substr(start, len)));
    }
    while (v.size() > 1 && v.back() == 0) v.pop_back();
    return v;
}

string vec_to_str(const vector<int> &v) {
    if (v.empty()) return "0";
    string res = to_string(v.back());
    char buf[3];
    for (int i = (int)v.size() - 2; i >= 0; --i) {
        snprintf(buf, sizeof(buf), "%02d", v[i]);
        res += buf;
    }
    return res;
}

/* -------------- multiplication via FFT ------- */
vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    if (a.empty() || b.empty()) return {};
    size_t n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    vector<cd> fa(n), fb(n);
    for (size_t i = 0; i < a.size(); ++i) fa[i] = cd(a[i], 0);
    for (size_t i = 0; i < b.size(); ++i) fb[i] = cd(b[i], 0);
    fft(fa, false);
    fft(fb, false);
    for (size_t i = 0; i < n; ++i) fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> tmp(n);
    for (size_t i = 0; i < n; ++i)
        tmp[i] = (long long)(fa[i].real() + 0.5);

    // carry propagation
    long long carry = 0;
    vector<int> res;
    res.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        long long cur = tmp[i] + carry;
        res.push_back(int(cur % BASE));
        carry = cur / BASE;
    }
    while (carry) {
        res.push_back(int(carry % BASE));
        carry /= BASE;
    }
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

/* -------------------- main -------------------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string n_str;
    long long m;
    while (cin >> n_str >> m) {
        if (n_str == "0" && m == 0) break;

        if (n_str == "0") {               // n == 0, m > 0
            cout << "0\n";
            continue;
        }
        if (m == 0) {                     // any n ^ 0 = 1
            cout << "1\n";
            continue;
        }
        if (n_str == "1") {               // 1 ^ anything = 1
            cout << "1\n";
            continue;
        }

        vector<int> base = str_to_vec(n_str);
        vector<int> result = {1};

        long long exp = m;
        while (exp > 0) {
            if (exp & 1LL) result = multiply(result, base);
            exp >>= 1LL;
            if (exp) base = multiply(base, base);
        }
        cout << vec_to_str(result) << '\n';
    }
    return 0;
}
