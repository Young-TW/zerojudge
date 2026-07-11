#include <iostream>

using namespace std;

typedef long long ll;
const int MOD = 100000007;

struct Matrix {
    ll a, b, c, d;
    Matrix(ll a = 0, ll b = 0, ll c = 0, ll d = 0) : a(a), b(b), c(c), d(d) {}
};

Matrix mul(const Matrix& x, const Matrix& y) {
    return Matrix(
        (x.a * y.a + x.b * y.c) % MOD,
        (x.a * y.b + x.b * y.d) % MOD,
        (x.c * y.a + x.d * y.c) % MOD,
        (x.c * y.b + x.d * y.d) % MOD
    );
}

Matrix power(Matrix base, ll exp) {
    Matrix res(1, 0, 0, 1);
    while (exp > 0) {
        if (exp % 2 == 1) res = mul(res, base);
        base = mul(base, base);
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll m, f, k;
    while (cin >> m >> f >> k) {
        Matrix M(0, 1, 1, 1);
        Matrix res = power(M, k + 1);
        ll ans = (m * res.b + f * res.d) % MOD;
        cout << ans << "\n";
    }
    
    return 0;
}
