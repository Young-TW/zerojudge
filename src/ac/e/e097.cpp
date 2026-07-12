#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int MAXA = 31623;
int primes[3500];
int prime_cnt = 0;
bool is_composite[MAXA + 1] = {false};

void sieve() {
    for (int i = 2; i <= MAXA; ++i) {
        if (!is_composite[i]) {
            primes[prime_cnt++] = i;
        }
        for (int j = 0; j < prime_cnt && i * primes[j] <= MAXA; ++j) {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

__int128 power(unsigned long long base, unsigned long long exp) {
    __int128 res = 1;
    __int128 b = base;
    while (exp > 0) {
        if (exp & 1) res *= b;
        b *= b;
        exp >>= 1;
    }
    return res;
}

vector<pair<unsigned long long, unsigned long long>> factorize(unsigned long long a) {
    vector<pair<unsigned long long, unsigned long long>> factors;
    if (a <= 1) return factors;
    for (int i = 0; i < prime_cnt; ++i) {
        if ((unsigned long long)primes[i] * primes[i] > a) break;
        if (a % primes[i] == 0) {
            unsigned long long cnt = 0;
            while (a % primes[i] == 0) {
                a /= primes[i];
                cnt++;
            }
            factors.push_back({primes[i], cnt});
        }
    }
    if (a > 1) {
        factors.push_back({a, 1});
    }
    return factors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int T, A, M;
    while (cin >> T >> A >> M) {
        for (int i = 0; i < T; ++i) {
            unsigned long long a, m, h;
            cin >> a >> m >> h;
            vector<pair<unsigned long long, unsigned long long>> factors = factorize(a);
            __int128 b = 1, c = 1;
            for (size_t j = 0; j < factors.size(); ++j) {
                unsigned long long p = factors[j].first;
                unsigned long long e = factors[j].second;
                unsigned long long total_exp = m * e;
                unsigned long long b_exp = total_exp / h;
                unsigned long long c_exp = total_exp - b_exp * h;
                b *= power(p, b_exp);
                c *= power(p, c_exp);
            }
            cout << (unsigned long long)b << " " << (unsigned long long)c << "\n";
        }
    }
    return 0;
}
