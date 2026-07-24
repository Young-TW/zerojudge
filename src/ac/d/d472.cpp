#include <iostream>
#include <vector>

using namespace std;

const int MOD = 76543;

vector<int> get_primes(int n) {
    vector<int> primes;
    vector<bool> is_comp(n + 1, false);
    for (int i = 2; i <= n; ++i) {
        if (!is_comp[i]) {
            primes.push_back(i);
        }
        for (size_t j = 0; j < primes.size(); ++j) {
            int p = primes[j];
            if (i * p > n) break;
            is_comp[i * p] = true;
            if (i % p == 0) break;
        }
    }
    return primes;
}

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> primes = get_primes(10000);
    
    long long ans = 1;
    long long k;
    int idx = 0;
    
    while (cin >> k) {
        if (idx < (int)primes.size()) {
            long long p = primes[idx];
            long long exp = k % (MOD - 1);
            ans = (ans * power(p, exp)) % MOD;
        }
        idx++;
    }
    
    cout << ans << "\n";
    
    return 0;
}
