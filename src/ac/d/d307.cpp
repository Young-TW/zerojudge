#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<int> queries;
    int n, maxN = 0;
    while (cin >> n) {
        if (n == 0) break;
        queries.push_back(n);
        if (n > maxN) maxN = n;
    }
    if (queries.empty()) return 0;

    // ---------- sieve ----------
    vector<bool> isPrime(maxN + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= maxN; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= maxN; j += i)
                isPrime[j] = false;
        }
    }

    // list of primes (including 2)
    vector<int> primes;
    for (int i = 2; i <= maxN; ++i)
        if (isPrime[i]) primes.push_back(i);

    // ---------- answer queries ----------
    for (int val : queries) {
        int cnt = 0;
        for (int p : primes) {
            if (p > val / 2) break;
            if (isPrime[val - p]) ++cnt;
        }
        cout << cnt << '\n';
    }
    return 0;
}
