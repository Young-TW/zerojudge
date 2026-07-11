#include <iostream>
#include <vector>

const int MOD = 998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    while (std::cin >> N) {
        std::vector<int> a(N + 1), b(N + 1);
        for (int i = 1; i <= N; ++i) std::cin >> a[i];
        for (int i = 1; i <= N; ++i) std::cin >> b[i];
        
        std::vector<int> F(N + 1, 0), G(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            if (a[i] == 0) continue;
            for (int j = i; j <= N; j += i) {
                F[j] += a[i];
                if (F[j] >= MOD) F[j] -= MOD;
            }
        }
        for (int i = 1; i <= N; ++i) {
            if (b[i] == 0) continue;
            for (int j = i; j <= N; j += i) {
                G[j] += b[i];
                if (G[j] >= MOD) G[j] -= MOD;
            }
        }
        
        std::vector<int> H(N + 1);
        for (int i = 1; i <= N; ++i) {
            H[i] = static_cast<int>((1LL * F[i] * G[i]) % MOD);
        }
        
        // Linear sieve for Möbius function
        std::vector<int> mu(N + 1, 0), primes;
        std::vector<int> is_composite(N + 1, 0);
        mu[1] = 1;
        for (int i = 2; i <= N; ++i) {
            if (!is_composite[i]) {
                primes.push_back(i);
                mu[i] = -1;
            }
            for (int p : primes) {
                long long ip = 1LL * i * p;
                if (ip > N) break;
                is_composite[ip] = 1;
                if (i % p == 0) {
                    mu[ip] = 0;
                    break;
                } else {
                    mu[ip] = -mu[i];
                }
            }
        }
        
        std::vector<long long> h(N + 1, 0);
        for (int d = 1; d <= N; ++d) {
            if (mu[d] == 0) continue;
            for (int k = d; k <= N; k += d) {
                int idx = k / d;
                h[k] += mu[d] * H[idx];
            }
        }
        
        for (int k = 1; k <= N; ++k) {
            long long val = h[k] % MOD;
            if (val < 0) val += MOD;
            std::cout << val << (k == N ? '\n' : ' ');
        }
    }
    return 0;
}
