#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
const ll MOD = 100019;

struct Matrix {
    ll a[3][3];
    Matrix() {
        memset(a, 0, sizeof(a));
    }
};

Matrix multiply(const Matrix& A, const Matrix& B) {
    Matrix C;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
            }
            C.a[i][j] = (C.a[i][j] % MOD + MOD) % MOD;
        }
    }
    return C;
}

Matrix mat_pow(Matrix A, ll p) {
    Matrix R;
    for (int i = 0; i < 3; ++i) R.a[i][i] = 1;
    while (p > 0) {
        if (p & 1) R = multiply(R, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return R;
}

void vec_mul(ll V[3], const Matrix& A) {
    ll R[3] = {0, 0, 0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            R[i] = (R[i] + A.a[i][j] * V[j]) % MOD;
        }
        R[i] = (R[i] % MOD + MOD) % MOD;
    }
    V[0] = R[0];
    V[1] = R[1];
    V[2] = R[2];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n;
    while (cin >> n) {
        if (n == 1) {
            cout << 1 << "\n";
            continue;
        }
        if (n == 2) {
            cout << 1 << "\n";
            continue;
        }
        if (n == 3) {
            cout << 2 << "\n";
            continue;
        }
        
        ll k = n / 3;
        Matrix M;
        M.a[0][0] = 3; M.a[0][1] = 2; M.a[0][2] = -2;
        M.a[1][0] = 2; M.a[1][1] = 1; M.a[1][2] = -1;
        M.a[2][0] = 0; M.a[2][1] = 0; M.a[2][2] = 1;
        
        Matrix Mk = mat_pow(M, k - 1);
        
        ll V[3] = {2, 1, 1};
        vec_mul(V, Mk);
        
        ll ans;
        if (n % 3 == 0) {
            ans = V[0];
        } else if (n % 3 == 1) {
            ans = (V[0] + V[1] - 1) % MOD;
        } else {
            ans = (2 * V[0] + V[1] - 1) % MOD;
        }
        
        ans = (ans % MOD + MOD) % MOD;
        cout << ans << "\n";
    }
    
    return 0;
}
