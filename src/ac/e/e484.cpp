#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 10005;

int min_prime_factor[MAXN];
vector<int> primes;

void linear_sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (min_prime_factor[i] == 0) {
            min_prime_factor[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > min_prime_factor[i] || i * p > n) break;
            min_prime_factor[i * p] = p;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    linear_sieve(MAXN - 1);

    int id;
    while (cin >> id) {
        bool is_prime = true;
        if (id < 2) {
            is_prime = false;
        } else {
            for (int p : primes) {
                if (p * p > id) break;
                if (id % p == 0) {
                    is_prime = false;
                    break;
                }
            }
        }
        cout << (is_prime ? "yes" : "no") << "\n";
    }

    return 0;
}
