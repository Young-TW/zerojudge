#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353LL;

struct Mat {
    long long a[2][2];
    Mat(bool ident = false) {
        a[0][0] = a[1][1] = ident ? 1 : 0;
        a[0][1] = a[1][0] = 0;
    }
};

Mat mul(const Mat& x, const Mat& y) {
    Mat r;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            __int128 sum = 0;
            for (int k = 0; k < 2; ++k)
                sum += (__int128)x.a[i][k] * y.a[k][j];
            r.a[i][j] = (long long)(sum % MOD);
        }
    return r;
}

Mat power(Mat base, unsigned long long exp) {
    Mat res(true);               // identity
    while (exp) {
        if (exp & 1ULL) res = mul(res, base);
        base = mul(base, base);
        exp >>= 1ULL;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long N;
    while (cin >> N) {
        if (N == 0) {                 // not required, but safe
            cout << 1 << '\n';
            continue;
        }
        if (N == 1) {
            cout << 6 << '\n';
            continue;
        }
        // matrix M
        Mat M;
        M.a[0][0] = 8 % MOD;
        M.a[0][1] = (MOD - 4) % MOD;   // -4 mod MOD
        M.a[1][0] = 1;
        M.a[1][1] = 0;

        Mat R = power(M, N - 1);       // M^(N-1)

        long long a1 = 6;   // a(1)
        long long a0 = 1;   // a(0)

        __int128 ans = (__int128)R.a[0][0] * a1 + (__int128)R.a[0][1] * a0;
        cout << (long long)(ans % MOD) << '\n';
    }
    return 0;
}
