#include <cstdio>
#include <vector>

using namespace std;

int main() {
    const int MAXN = 1000;
    vector<bool> isPrime(MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= MAXN; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int N;
    while (scanf("%d", &N) == 1) {
        vector<int> primes;
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) primes.push_back(i);
        }
        int cnt = 0;
        for (int i = 0; i < (int)primes.size(); i++) {
            printf("%10d", primes[i]);
            cnt++;
            if (cnt == 5) {
                printf("\n");
                cnt = 0;
            }
        }
        if (cnt != 0) {
            printf("\n");
        }
    }
    return 0;
}
