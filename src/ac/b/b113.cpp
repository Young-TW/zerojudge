#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

using i128 = __int128;

static i128 abs128(i128 x) { return x >= 0 ? x : -x; }

static i128 gcd128(i128 a, i128 b) {
    a = abs128(a); b = abs128(b);
    while (b != 0) {
        i128 t = a % b;
        a = b;
        b = t;
    }
    return a == 0 ? 1 : a;
}

struct Rat {
    i128 p, q;
    Rat() : p(0), q(1) {}
    Rat(i128 P, i128 Q = 1) : p(P), q(Q) { norm(); }
    void norm() {
        if (q < 0) { p = -p; q = -q; }
        if (p == 0) { q = 1; return; }
        i128 g = gcd128(p, q);
        p /= g; q /= g;
    }
    bool isZero() const { return p == 0; }
};

static Rat operator+(const Rat& a, const Rat& b) {
    if (a.p == 0) return b;
    if (b.p == 0) return a;
    i128 g = gcd128(a.q, b.q);
    i128 aq = a.q / g, bq = b.q / g;
    return Rat(a.p * bq + b.p * aq, aq * b.q);
}

static Rat operator-(const Rat& a, const Rat& b) {
    if (b.p == 0) return a;
    if (a.p == 0) return Rat(-b.p, b.q);
    i128 g = gcd128(a.q, b.q);
    i128 aq = a.q / g, bq = b.q / g;
    return Rat(a.p * bq - b.p * aq, aq * b.q);
}

static Rat operator*(const Rat& a, const Rat& b) {
    if (a.p == 0 || b.p == 0) return Rat(0, 1);
    i128 g1 = gcd128(a.p, b.q);
    i128 g2 = gcd128(b.p, a.q);
    i128 ap = a.p / g1, bq = b.q / g1;
    i128 bp = b.p / g2, aq = a.q / g2;
    return Rat(ap * bp, aq * bq);
}

static Rat operator/(const Rat& a, const Rat& b) {
    if (a.p == 0) return Rat(0, 1);
    return a * Rat(b.q, b.p);
}

static string toString(i128 x) {
    if (x == 0) return "0";
    bool neg = x < 0;
    if (neg) x = -x;
    string s;
    while (x > 0) {
        s.push_back(char('0' + int(x % 10)));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

static ostream& operator<<(ostream& os, const Rat& r) {
    if (r.q == 1) os << toString(r.p);
    else os << toString(r.p) << '/' << toString(r.q);
    return os;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long nll;
    if (!(cin >> nll)) return 0;
    int n = int(nll);
    if (n <= 0) return 0;

    vector<long long> raw;
    long long x;
    while (cin >> x) raw.push_back(x);

    int w = n + 1;
    int m = int(raw.size() / w);
    vector<vector<Rat>> a(m, vector<Rat>(n + 1));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j <= n; ++j)
            a[i][j] = Rat(i128(raw[i * w + j]));

    int r = 0;
    vector<int> pc, pr;
    for (int col = 0; col < n && r < m; ++col) {
        int sel = -1;
        for (int i = r; i < m; ++i) {
            if (!a[i][col].isZero()) { sel = i; break; }
        }
        if (sel == -1) continue;
        if (sel != r) swap(a[sel], a[r]);

        Rat inv = Rat(1, 1) / a[r][col];
        for (int j = col; j <= n; ++j) a[r][j] = a[r][j] * inv;

        for (int i = 0; i < m; ++i) {
            if (i == r || a[i][col].isZero()) continue;
            Rat f = a[i][col];
            for (int j = col; j <= n; ++j)
                a[i][j] = a[i][j] - f * a[r][j];
        }
        pc.push_back(col);
        pr.push_back(r);
        ++r;
    }

    for (int i = 0; i < m; ++i) {
        bool all = true;
        for (int j = 0; j < n; ++j) {
            if (!a[i][j].isZero()) { all = false; break; }
        }
        if (all && !a[i][n].isZero()) {
            cout << "0\n";
            return 0;
        }
    }

    if (r < n) {
        cout << "N\n";
        return 0;
    }

    vector<Rat> ans(n);
    for (int i = 0; i < int(pc.size()); ++i)
        ans[pc[i]] = a[pr[i]][n];

    cout << "1\n";
    for (int i = 0; i < n; ++i)
        cout << "x" << i + 1 << " = " << ans[i] << "\n";
    return 0;
}
