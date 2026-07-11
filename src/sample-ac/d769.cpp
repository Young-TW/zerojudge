#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 5281;

struct Matrix {
    int a[55][55];
    Matrix() {
        memset(a, 0, sizeof(a));
    }
};

int N, k;

Matrix mul(const Matrix &A, const Matrix &B) {
    Matrix C;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            long long sum = 0;
            for (int l = 1; l <= N; ++l) {
                sum += A.a[i][l] * B.a[l][j];
            }
            C.a[i][j] = sum % MOD;
        }
    }
    return C;
}

Matrix mat_pow(Matrix A, int p) {
    Matrix R;
    for (int i = 1; i <= N; ++i) {
        R.a[i][i] = 1;
    }
    while (p > 0) {
        if (p & 1) {
            R = mul(R, A);
        }
        A = mul(A, A);
        p >>= 1;
    }
    return R;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> N >> k) {
        Matrix adj;
        int x, y, s;
        while (cin >> x >> y >> s) {
            if (x == 0 && y == 0 && s == 0) break;
            adj.a[x][y] = s;
        }
        
        Matrix res = mat_pow(adj, k);
        
        int Q;
        cin >> Q;
        while (Q--) {
            int i, j;
            cin >> i >> j;
            cout << res.a[i][j] << "\n";
        }
    }
    
    return 0;
}
