#include <iostream>
#include <vector>

using namespace std;

const int MAXP = 1000000;
vector<int> primes;
bool is_composite[MAXP + 1];

void sieve() {
    for (int i = 2; i <= MAXP; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            for (long long j = 1LL * i * i; j <= MAXP; j += i) {
                is_composite[j] = true;
            }
        }
    }
}

long long calculate_sigma(long long n) {
    long long sum = 1;
    long long temp = n;
    for (int p : primes) {
        if (1LL * p * p > temp) break;
        if (temp % p == 0) {
            long long power = 1;
            long long term = 1;
            while (temp % p == 0) {
                temp /= p;
                power *= p;
                term += power;
            }
            sum *= term;
        }
    }
    if (temp > 1) {
        sum *= (1 + temp);
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve();
    
    int t;
    while (cin >> t) {
        while (t--) {
            long long n;
            cin >> n;
            long long sigma = calculate_sigma(n);
            long long sum_divisors = sigma - n;
            if (sum_divisors == n) {
                cout << "perfect\n";
            } else if (sum_divisors < n) {
                cout << "deficient\n";
            } else {
                cout << "abundant\n";
            }
        }
    }
    return 0;
}
