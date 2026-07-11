#include <iostream>

using namespace std;

const long long P = 1000007;

struct Matrix {
    long long a[3][3];
};

struct Vector {
    long long v[3];
};

long long norm(long long x) {
    return (x % P + P) % P;
}

Matrix multiply(const Matrix& A, const Matrix& B) {
    Matrix C;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            long long sum = 0;
            for (int k = 0; k < 3; ++k) {
                sum = (sum + A.a[i][k] * B.a[k][j]) % P;
            }
            C.a[i][j] = sum;
        }
    }
    return C;
}

Vector multiply(const Matrix& A, const Vector& V) {
    Vector R;
    for (int i = 0; i < 3; ++i) {
        long long sum = 0;
        for (int j = 0; j < 3; ++j) {
            sum = (sum + A.a[i][j] * V.v[j]) % P;
        }
        R.v[i] = sum;
    }
    return R;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m, k, f0, f1, f2;
    while (cin >> n >> m >> k >> f0 >> f1 >> f2) {
        n = norm(n); m = norm(m); k = norm(k);
        f0 = norm(f0); f1 = norm(f1); f2 = norm(f2);
        
        Matrix base[64];
        base[0].a[0][0] = n; base[0].a[0][1] = m; base[0].a[0][2] = k;
        base[0].a[1][0] = 1; base[0].a[1][1] = 0; base[0].a[1][2] = 0;
        base[0].a[2][0] = 0; base[0].a[2][1] = 1; base[0].a[2][2] = 0;
        
        for (int i = 1; i < 63; ++i) {
            base[i] = multiply(base[i-1], base[i-1]);
        }
        
        int r;
        cin >> r;
        for (int i = 0; i < r; ++i) {
            long long x;
            cin >> x;
            if (x == 0) {
                cout << f0 << "\n";
            } else if (x == 1) {
                cout << f1 << "\n";
            } else if (x == 2) {
                cout << f2 << "\n";
            } else {
                Vector V;
                V.v[0] = f2; V.v[1] = f1; V.v[2] = f0;
                long long p = x - 2;
                for (int j = 0; j < 63; ++j) {
                    if ((p >> j) & 1) {
                        V = multiply(base[j], V);
                    }
                }
                cout << V.v[0] << "\n";
            }
        }
    }
    return 0;
}
