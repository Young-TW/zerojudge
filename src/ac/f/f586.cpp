#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000005;
int mu[MAXN];
vector<int> primes;
bool is_composite[MAXN];

void sieve() {
    mu[1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (size_t j = 0; j < primes.size(); ++j) {
            int p = primes[j];
            if (i * p >= MAXN) break;
            is_composite[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            cout << mu[N] << "\n";
        }
    }
    return 0;
}
