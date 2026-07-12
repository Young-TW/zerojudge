#include <iostream>

using namespace std;

const long long MOD = 998244353;

void multiply(long long *c, const long long *a, const long long *b, int K) {
    long long temp[155];
    for (int i = 0; i < K; i++) {
        temp[i] = 0;
        for (int j = 0; j < K; j++) {
            temp[i] = (temp[i] + a[j] * b[(i - j + K) % K]) % MOD;
        }
    }
    for (int i = 0; i < K; i++) c[i] = temp[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    int K;
    while (cin >> N >> K) {
        long long b[155];
        for (int i = 0; i < K; i++) b[i] = 0;
        b[0] = 1;
        
        for (int i = 1; i <= K; i++) {
            long long temp[155];
            for (int j = 0; j < K; j++) {
                temp[j] = (b[j] + b[(j + i) % K]) % MOD;
            }
            for (int j = 0; j < K; j++) b[j] = temp[j];
        }
        
        long long q = N / K;
        long long r = N % K;
        
        long long res[155];
        for (int i = 0; i < K; i++) res[i] = 0;
        res[0] = 1;
        
        long long base[155];
        for (int i = 0; i < K; i++) base[i] = b[i];
        
        while (q > 0) {
            if (q & 1) {
                multiply(res, res, base, K);
            }
            multiply(base, base, base, K);
            q >>= 1;
        }
        
        long long v[155];
        for (int i = 0; i < K; i++) v[i] = res[i];
        
        for (int i = 1; i <= r; i++) {
            long long temp[155];
            for (int j = 0; j < K; j++) {
                temp[j] = (v[j] + v[(j + i) % K]) % MOD;
            }
            for (int j = 0; j < K; j++) v[j] = temp[j];
        }
        
        cout << v[0] << "\n";
    }
    
    return 0;
}
