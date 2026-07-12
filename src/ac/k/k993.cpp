#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, p;
    while (cin >> n >> p) {
        vector<long long> f(n + 1);
        vector<long long> inv(n + 2);
        inv[1] = 1;
        for (long long i = 2; i <= n + 1; ++i) {
            inv[i] = (p - (p / i) * inv[p % i] % p) % p;
        }
        f[1] = 0;
        for (long long i = 2; i <= n; ++i) {
            long long L = i / 2;
            long long R = i - L;
            long long term = (L * inv[R + 1]) % p;
            term = (term + R * inv[L + 1]) % p;
            f[i] = (f[L] + f[R] + i - term) % p;
            if (f[i] < 0) f[i] += p;
        }
        for (long long i = 1; i <= n; ++i) {
            cout << f[i] << "\n";
        }
    }
    return 0;
}
