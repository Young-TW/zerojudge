#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int P = 998244353, G = 3;

long long power(long long a, long long b) {
    long long res = 1;
    a %= P;
    while (b > 0) {
        if (b & 1) res = res * a % P;
        a = a * a % P;
        b >>= 1;
    }
    return res;
}

void ntt(vector<long long>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        long long w = invert ? power(G, P - 1 - (P - 1) / len) : power(G, (P - 1) / len);
        for (int i = 0; i < n; i += len) {
            long long wn = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j];
                long long v = a[i + j + len / 2] * wn % P;
                a[i + j] = (u + v) % P;
                a[i + j + len / 2] = (u - v + P) % P;
                wn = wn * w % P;
            }
        }
    }
    if (invert) {
        long long n_inv = power(n, P - 2);
        for (int i = 0; i < n; i++) {
            a[i] = a[i] * n_inv % P;
        }
    }
}

int main() {
    int n;
    long long k;
    if (scanf("%d %lld", &n, &k) != 2) return 0;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    
    vector<long long> inv(n + 1);
    if (n >= 1) inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (P - (P / i) * inv[P % i] % P) % P;
    }
    
    vector<long long> c(n);
    c[0] = 1;
    for (int i = 1; i < n; i++) {
        c[i] = c[i - 1] * ((k + i - 1) % P) % P * inv[i] % P;
    }
    
    int N = 1;
    while (N < 2 * n) N <<= 1;
    
    vector<long long> A(N, 0), C(N, 0);
    for (int i = 0; i < n; i++) {
        A[i] = a[i];
        C[i] = c[i];
    }
    
    ntt(A, false);
    ntt(C, false);
    for (int i = 0; i < N; i++) {
        A[i] = A[i] * C[i] % P;
    }
    ntt(A, true);
    
    for (int i = 0; i < n; i++) {
        printf("%lld%c", A[i], (i == n - 1) ? '\n' : ' ');
    }
    
    return 0;
}
