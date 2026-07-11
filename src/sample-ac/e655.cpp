#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 10005;
bool is_prime[MAXN];
vector<int> primes;

void sieve() {
    fill(is_prime, is_prime + MAXN, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAXN; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int M;
    if (cin >> M) {
        while (M--) {
            int n;
            if (!(cin >> n)) break;
            int max_rem = -1;
            int best_x = -1;
            for (int p : primes) {
                if (p > n) break;
                int rem = n % p;
                if (rem > max_rem) {
                    max_rem = rem;
                    best_x = p;
                }
            }
            cout << best_x << "\n";
        }
    }
    return 0;
}
