#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

void fwht(vector<long long>& a) {
    int n = a.size();
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = i; j < i + len; ++j) {
                long long u = a[j];
                long long v = a[j + len];
                a[j] = u + v;
                if (a[j] >= MOD) a[j] -= MOD;
                a[j + len] = u - v;
                if (a[j + len] < 0) a[j + len] += MOD;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];
        
        fwht(a);
        fwht(b);
        
        for (int i = 0; i < n; ++i) {
            a[i] = (a[i] * b[i]) % MOD;
        }
        
        fwht(a);
        
        long long inv_n = power(n, MOD - 2, MOD);
        for (int i = 0; i < n; ++i) {
            a[i] = (a[i] * inv_n) % MOD;
        }
        
        for (int i = 0; i < n; ++i) {
            cout << a[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
