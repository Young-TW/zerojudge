#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1.0);

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
    int N, M;
    while (cin >> N >> M) {
        vector<long long> a(N), b(M);
        for (int i = 0; i < N; ++i) cin >> a[i];
        for (int i = 0; i < M; ++i) cin >> b[i];

        int need = N + M - 1;
        int L = 1;
        while (L < need) L <<= 1;

        vector<cd> FA(L), FB(L);
        for (int i = 0; i < N; ++i) FA[i] = cd((double)a[i], 0);
        for (int i = N; i < L; ++i) FA[i] = cd(0, 0);
        for (int i = 0; i < M; ++i) FB[i] = cd((double)b[i], 0);
        for (int i = M; i < L; ++i) FB[i] = cd(0, 0);

        fft(FA, false);
        fft(FB, false);
        for (int i = 0; i < L; ++i) FA[i] *= FB[i];
        fft(FA, true);

        long long bestVal = -1;
        int bestTower = -1;               // tower index (1‑based)
        for (int k = 0; k < need; ++k) {
            long long cur = (long long)(FA[k].real() + 0.5);
            int tower = k + 2;            // because levels start from 1
            if (cur > bestVal || (cur == bestVal && tower < bestTower)) {
                bestVal = cur;
                bestTower = tower;
            }
        }
        cout << bestTower << ' ' << bestVal << '\n';
    }
    return 0;
}
