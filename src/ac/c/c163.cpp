#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1.0);

/* iterative Cooley–Tukey FFT */
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<int> vals(n);
        int maxv = 0;
        for (int i = 0; i < n; ++i) {
            cin >> vals[i];
            if (vals[i] > maxv) maxv = vals[i];
        }

        int sz = 1;
        while (sz <= 2 * maxv) sz <<= 1;

        vector<cd> f(sz);
        vector<char> present(maxv + 1, 0);
        for (int v : vals) {
            f[v] = cd(1.0, 0.0);
            present[v] = 1;
        }

        fft(f, false);
        for (int i = 0; i < sz; ++i) f[i] *= f[i];
        fft(f, true);

        long long answer = 0;
        for (int x : vals) {
            long long cnt = (long long)(f[x].real() + 0.5); // C[x]
            if ((x & 1) == 0 && present[x / 2]) cnt -= 1;   // remove (a,a) if present
            if (cnt > 0) ++answer;
        }
        cout << answer << '\n';
    }
    return 0;
}
