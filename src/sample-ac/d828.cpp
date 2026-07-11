#include <iostream>

using namespace std;

struct Matrix {
    long long a, b, c, d;
};

Matrix multiply(const Matrix& x, const Matrix& y) {
    Matrix res;
    res.a = (x.a * y.a + x.b * y.c) % 10000;
    res.b = (x.a * y.b + x.b * y.d) % 10000;
    res.c = (x.c * y.a + x.d * y.c) % 10000;
    res.d = (x.c * y.b + x.d * y.d) % 10000;
    return res;
}

Matrix mat_pow(Matrix base, long long exp) {
    Matrix res = {1, 0, 0, 1};
    while (exp > 0) {
        if (exp & 1) {
            res = multiply(res, base);
        }
        base = multiply(base, base);
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n) {
        Matrix base = {1, 1, 1, 0};
        Matrix res = mat_pow(base, n);
        cout << res.a << "\n";
    }
    
    return 0;
}
