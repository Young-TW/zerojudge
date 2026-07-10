#include <cstdio>
#include <vector>

using namespace std;

const int LIMIT = 44722; // ceil(sqrt(2000000000)) ~ 44721.36
bool is_comp[LIMIT + 1];
vector<int> primes;

void sieve() {
    for (int i = 2; i <= LIMIT; i++) {
        if (!is_comp[i]) {
            primes.push_back(i);
            for (long long j = (long long)i * i; j <= LIMIT; j += i)
                is_comp[j] = true;
        }
    }
}

long long factor_sum(long long n) {
    long long sum = 0;
    for (size_t i = 0; i < primes.size(); i++) {
        int p = primes[i];
        if ((long long)p * p > n) break;
        while (n % p == 0) {
            sum += p;
            n /= p;
        }
    }
    if (n > 1) sum += n;
    return sum;
}

int main() {
    sieve();
    long long x;
    while (scanf("%lld", &x) == 1) {
        printf("%lld\n", factor_sum(x));
    }
    return 0;
}
