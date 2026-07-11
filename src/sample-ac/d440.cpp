#include <iostream>
#include <vector>

using namespace std;

const int MAX_PRIME = 31623;
vector<int> primes;

void sieve() {
    vector<bool> is_prime(MAX_PRIME, true);
    for (int i = 2; i < MAX_PRIME; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j < MAX_PRIME; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    sieve();
    
    long long n;
    while (cin >> n && n) {
        if (n == 1) {
            cout << 0 << "\n";
            continue;
        }
        long long ans = n;
        long long temp = n;
        for (int p : primes) {
            if ((long long)p * p > temp) break;
            if (temp % p == 0) {
                ans = ans / p * (p - 1);
                while (temp % p == 0) {
                    temp /= p;
                }
            }
        }
        if (temp > 1) {
            ans = ans / temp * (temp - 1);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
