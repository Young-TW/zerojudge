#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<pair<long long,long long>> queries;
    long long n, m;
    long long maxL = 0;
    while (cin >> n >> m) {
        queries.emplace_back(n, m);
        long long L = min(n, m);
        if (L > maxL) maxL = L;
    }
    if (queries.empty()) return 0;

    // linear sieve for phi up to maxL
    vector<int> phi(maxL + 1);
    vector<int> primes;
    vector<bool> is_composite(maxL + 1, false);
    phi[0] = 0;
    if (maxL >= 1) phi[1] = 1;
    for (int i = 2; i <= maxL; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : primes) {
            long long v = 1LL * i * p;
            if (v > maxL) break;
            is_composite[v] = true;
            if (i % p == 0) {
                phi[v] = phi[i] * p;
                break;
            } else {
                phi[v] = phi[i] * (p - 1);
            }
        }
    }

    for (auto &qr : queries) {
        n = qr.first;
        m = qr.second;
        long long L = min(n, m);
        long long sum = 0;
        for (long long i = 1; i <= L; ++i) {
            long long cnt = (n / i) * (m / i);
            sum += (long long)phi[i] * cnt;
        }
        long long ans = 2 * sum - n * m;
        cout << ans << '\n';
    }
    return 0;
}
