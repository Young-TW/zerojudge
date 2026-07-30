#include <iostream>
#include <vector>
using namespace std;

int main() {
    // sieve up to sqrt(1e8) = 10000
    const int LIM = 10000;
    vector<int> primes;
    vector<bool> isC(LIM + 1, false);
    for (int i = 2; i <= LIM; ++i) {
        if (!isC[i]) {
            primes.push_back(i);
            for (long long j = (long long)i * i; j <= LIM; j += i) isC[j] = true;
        }
    }

    long long a, b;
    while (cin >> a >> b) {
        int cnt = 0;
        int len = (int)(b - a + 1);
        vector<bool> comp(len, false);
        for (int p : primes) {
            if ((long long)p * p > b) break;
            long long start = max((long long)p * p, ((a + p - 1) / p) * (long long)p);
            for (long long j = start; j <= b; j += p) {
                comp[(size_t)(j - a)] = true;
            }
        }
        for (int i = 0; i < len; ++i) {
            long long v = a + i;
            if (v >= 2 && !comp[i]) cnt++;
        }
        cout << cnt << "\n";
    }
    return 0;
}
