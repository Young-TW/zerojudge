#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

struct Mat {
    long long a[3][3];
    Mat(bool ident = false) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                a[i][j] = (ident && i == j) ? 1 : 0;
    }
};

Mat mul(const Mat& x, const Mat& y) {
    Mat r;
    for (int i = 0; i < 3; ++i)
        for (int k = 0; k < 3; ++k) if (x.a[i][k])
            for (int j = 0; j < 3; ++j) {
                r.a[i][j] = (r.a[i][j] + x.a[i][k] * y.a[k][j]) % MOD;
            }
    return r;
}

Mat mpow(Mat base, long long exp) {
    Mat res(true);               // identity
    while (exp > 0) {
        if (exp & 1) res = mul(res, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return res;
}

long long solve(long long L) {
    if (L == 0) return 1;          // not required by problem, but convenient
    if (L == 1) return 0;
    if (L == 2) return 1;

    // transition matrix
    Mat M;
    M.a[0][0] = 2; M.a[0][1] = 0; M.a[0][2] = 1;
    M.a[1][0] = 1; M.a[1][1] = 0; M.a[1][2] = 0;
    M.a[2][0] = 0; M.a[2][1] = 1; M.a[2][2] = 0;

    Mat P = mpow(M, L - 2);

    // V2 = [a2, a1, a0] = [1,0,1]
    long long a2 = 1, a1 = 0, a0 = 1;
    long long ans = (P.a[0][0] * a2 + P.a[0][1] * a1 + P.a[0][2] * a0) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long L;
    while (cin >> L) {
        cout << solve(L) << '\n';
    }
    return 0;
}
