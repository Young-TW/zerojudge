#include <iostream>
#include <vector>

using namespace std;

const int MAXP = 31623;
vector<int> primes;

void sieve() {
    vector<bool> is_prime(MAXP + 1, true);
    for (int i = 2; i <= MAXP; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = (long long)i * i; j <= MAXP; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

const int MAX_LEN = 10005;
long long rem[MAX_LEN];
int cnt[MAX_LEN];

void solve(long long L, long long U) {
    int len = U - L + 1;
    for (int i = 0; i < len; ++i) {
        rem[i] = L + i;
        cnt[i] = 1;
    }

    for (int p : primes) {
        if ((long long)p * p > U) break;
        long long start = ((L + p - 1) / p) * p;
        for (long long j = start; j <= U; j += p) {
            int idx = j - L;
            int e = 0;
            while (rem[idx] % p == 0) {
                rem[idx] /= p;
                e++;
            }
            cnt[idx] *= (e + 1);
        }
    }

    for (int i = 0; i < len; ++i) {
        if (rem[i] > 1) {
            cnt[i] *= 2;
        }
    }

    int max_d = 0;
    long long best_p = 0;
    for (int i = 0; i < len; ++i) {
        if (cnt[i] > max_d) {
            max_d = cnt[i];
            best_p = L + i;
        }
    }

    cout << "Between " << L << " and " << U << ", " << best_p << " has a maximum of " << max_d << " divisors.\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int N;
    if (cin >> N) {
        while (N--) {
            long long L, U;
            if (cin >> L >> U) {
                solve(L, U);
            } else {
                break;
            }
        }
    }
    return 0;
}
