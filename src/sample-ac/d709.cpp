#include <cstdio>

const int MAXN = 1000000;
bool is_prime[MAXN + 1];

void sieve() {
    for (int i = 2; i <= MAXN; ++i) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAXN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    sieve();
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        printf("%d\n", is_prime[n] ? 0 : 1);
    }
    return 0;
}
