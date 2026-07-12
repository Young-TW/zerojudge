#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXC = 10000005;
const int MOD = 1000000007;

int phi[MAXC];
int F[MAXC];
long long S[MAXC]; // S[k] = sum_{i=1}^{k} (number of pairs (a,b) with gcd(a,b)=i) * F[i] ? No.
// Let's redefine.
// We need Ans(n, m) = sum_{g=1}^{min(n,m)} F[g] * Count(n, m, g)
// Count(n, m, g) = number of pairs (a, b) such that 1<=a<=n, 1<=b<=m, gcd(a, b) = g.
// Count(n, m, g) = sum_{k=1}^{floor(min(n,m)/g)} mu[k] * floor(n/(g*k)) * floor(m/(g*k))
// This is O(N) per query if done naively. We need faster.
// Let T = g*k. Then g = T/k? No.
// Sum_{g} F[g] * Sum_{k} mu[k] * (n/(g*k)) * (m/(g*k))
// Let T = g*k. Then k = T/g.
// Sum_{T=1}^{min(n,m)} (n/T) * (m/T) * Sum_{g|T} F[g] * mu[T/g]
// Let H[T] = Sum_{g|T} F[g] * mu[T/g]. This is Dirichlet convolution (F * mu)[T].
// Then Ans(n, m) = Sum_{T=1}^{min(n,m)} (n/T) * (m/T) * H[T].
// We can precompute H[T] for all T up to MAXC.
// Then we can compute prefix sums of H? No, because the term (n/T)*(m/T) changes.
// But we can use square root decomposition (number theory blocking) on T.
// The values of n/T and m/T are constant over ranges.
// So we need prefix sums of H to quickly calculate sum of H[T] over a range [L, R].
// Let PrefH[x] = sum_{i=1}^{x} H[i].
// Then Ans(n, m) = sum_{ranges} (n/T) * (m/T) * (PrefH[R] - PrefH[L-1]).

long long PrefH[MAXC];
int mu[MAXC];
bool is_prime[MAXC];
vector<int> primes;

void sieve() {
    fill(is_prime, is_prime + MAXC, true);
    is_prime[0] = is_prime[1] = false;
    mu[1] = 1;
    phi[1] = 1; // Though phi not used in final formula, good to have if needed
    
    for (int i = 2; i < MAXC; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (size_t j = 0; j < primes.size(); ++j) {
            int p = primes[j];
            if (i * p >= MAXC) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                phi[i * p] = phi[i] * p;
                break;
            } else {
                mu[i * p] = -mu[i];
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}

void precompute() {
    sieve();
    
    // Compute Fibonacci numbers
    F[1] = 1;
    if (MAXC > 2) F[2] = 1;
    for (int i = 3; i < MAXC; ++i) {
        F[i] = (F[i-1] + F[i-2]) % MOD;
    }
    
    // Compute H[T] = sum_{d|T} F[d] * mu[T/d]
    // We can do this by iterating d and adding F[d]*mu[k] to H[d*k]
    vector<long long> H(MAXC, 0);
    
    for (int d = 1; d < MAXC; ++d) {
        if (F[d] == 0) continue; // Optimization
        for (int k = 1; ; ++k) {
            long long idx = (long long)d * k;
            if (idx >= MAXC) break;
            if (mu[k] == 0) continue;
            
            long long term = (1LL * F[d] * mu[k]) % MOD;
            if (term < 0) term += MOD;
            
            H[idx] = (H[idx] + term) % MOD;
        }
    }
    
    // Compute Prefix Sum of H
    PrefH[0] = 0;
    for (int i = 1; i < MAXC; ++i) {
        PrefH[i] = (PrefH[i-1] + H[i]) % MOD;
    }
}

long long solve(int n, int m) {
    if (n > m) swap(n, m);
    long long ans = 0;
    
    for (int l = 1, r; l <= n; l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        long long count_n = n / l;
        long long count_m = m / l;
        long long sum_H = (PrefH[r] - PrefH[l-1] + MOD) % MOD;
        
        long long term = (count_n * count_m) % MOD;
        term = (term * sum_H) % MOD;
        
        ans = (ans + term) % MOD;
    }
    
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    precompute();
    
    int C, T;
    if (!(cin >> C >> T)) return 0;
    
    while (T--) {
        int n, m;
        cin >> n >> m;
        cout << solve(n, m) << "\n";
    }
    
    return 0;
}
