#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using u64   = unsigned long long;

const int LIMIT = 2000000;                 // pre‑compute up to this value

vector<int> phi(LIMIT + 1);
vector<u64> pref(LIMIT + 1);
unordered_map<int64, u64> memo;

/* linear sieve for φ */
void init_phi() {
    vector<int> primes;
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= LIMIT; ++i) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            primes.push_back(i);
        }
        for (int p : primes) {
            long long v = 1LL * i * p;
            if (v > LIMIT) break;
            if (i % p == 0) {
                phi[v] = phi[i] * p;
                break;
            } else {
                phi[v] = phi[i] * (p - 1);
            }
        }
    }
    pref[0] = 0;
    for (int i = 1; i <= LIMIT; ++i) pref[i] = pref[i - 1] + (u64)phi[i];
}

/* recursive computation of Σ_{k=1}^{n} φ(k) */
u64 sum_phi(int64 n) {
    if (n <= LIMIT) return pref[(int)n];
    auto it = memo.find(n);
    if (it != memo.end()) return it->second;

    u64 ans = (u64)n * (u64)(n + 1) / 2;   // n·(n+1)/2
    int64 i = 2;
    while (i <= n) {
        int64 q = n / i;
        int64 nxt = n / q;                // last i with the same q
        ans -= (u64)(nxt - i + 1) * sum_phi(q);
        i = nxt + 1;
    }
    memo[n] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_phi();

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int64 N;
        cin >> N;
        cout << sum_phi(N) << '\n';
    }
    return 0;
}
