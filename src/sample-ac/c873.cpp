#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007LL;

struct Matrix {
    ll a[3][3];
    Matrix() {
        memset(a, 0, sizeof(a));
    }
};

Matrix mul(const Matrix& A, const Matrix& B) {
    Matrix C;
    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 3; ++k) {
            if (A.a[i][k] == 0) continue;
            for (int j = 0; j < 3; ++j) {
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
            }
        }
    }
    return C;
}

void mulVec(const Matrix& A, ll v[3]) {
    ll res[3];
    res[0] = (A.a[0][0] * v[0] + A.a[0][1] * v[1] + A.a[0][2] * v[2]) % MOD;
    res[1] = (A.a[1][0] * v[0] + A.a[1][1] * v[1] + A.a[1][2] * v[2]) % MOD;
    res[2] = (A.a[2][0] * v[0] + A.a[2][1] * v[1] + A.a[2][2] * v[2]) % MOD;
    v[0] = res[0];
    v[1] = res[1];
    v[2] = res[2];
}

Matrix A_pow[64];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll m, n1, n2;
    if (!(cin >> m >> n1 >> n2)) return 0;
    m = (m % MOD + MOD) % MOD;
    n1 = (n1 % MOD + MOD) % MOD;
    n2 = (n2 % MOD + MOD) % MOD;

    A_pow[0].a[0][0] = 1; A_pow[0].a[0][1] = 1; A_pow[0].a[0][2] = 1;
    A_pow[0].a[1][0] = 2; A_pow[0].a[1][1] = 1; A_pow[0].a[1][2] = 0;
    A_pow[0].a[2][0] = 3; A_pow[0].a[2][1] = 2; A_pow[0].a[2][2] = 1;

    for (int i = 1; i < 64; ++i) {
        A_pow[i] = mul(A_pow[i-1], A_pow[i-1]);
    }

    int T;
    cin >> T;
    while (T--) {
        ll k;
        cin >> k;
        ll v[3] = {m, n1, n2};
        for (int i = 0; i < 64; ++i) {
            if (k & (1LL << i)) {
                mulVec(A_pow[i], v);
            }
        }
        cout << v[1] << " " << v[2] << "\n";
    }

    return 0;
}
