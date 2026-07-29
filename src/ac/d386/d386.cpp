#include <bits/stdc++.h>
using namespace std;

bool isPrimeLL(long long x, const vector<int>& primes) {
    if (x < 2) return false;
    for (int p : primes) {
        long long pp = 1LL * p * p;
        if (pp > x) break;
        if (x % p == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAX_N = 10000;
    const long long MAX_VAL = 1LL * MAX_N * MAX_N + MAX_N + 41;
    const int LIM = static_cast<int>(std::sqrt(static_cast<double>(MAX_VAL))) + 1;

    // sieve up to LIM
    vector<bool> comp(LIM + 1, false);
    vector<int> primes;
    for (int i = 2; i <= LIM; ++i) {
        if (!comp[i]) {
            primes.push_back(i);
            if (1LL * i * i <= LIM)
                for (int j = i * i; j <= LIM; j += i)
                    comp[j] = true;
        }
    }

    // prefix of prime counts for f(n)
    vector<int> pref(MAX_N + 2, 0);          // pref[0] … pref[10001]
    for (int i = 0; i <= MAX_N; ++i) {
        long long val = 1LL * i * i + i + 41;
        pref[i + 1] = pref[i] + (isPrimeLL(val, primes) ? 1 : 0);
    }

    int a, b;
    while (cin >> a >> b) {
        long long primeCnt = pref[b + 1] - pref[a];
        long long total = b - a + 1;
        // percentage with 2 decimals => round(primeCnt*10000/total) hundredths,
        // rounded half-up via pure integer arithmetic to avoid float error.
        long long q = (2 * primeCnt * 10000 + total) / (2 * total); // floor of exact+0.5
        long long ip = q / 100, fp = q % 100;
        cout << ip << '.' << setw(2) << setfill('0') << fp << '\n';
    }
    return 0;
}
