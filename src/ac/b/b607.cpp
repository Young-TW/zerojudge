#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;

bool isPrime[MAXN];
vector<int> primes;
int bestGoldbach[MAXN];          // for even numbers only, -1 otherwise

void sieve() {
    fill(isPrime, isPrime + MAXN, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i < MAXN; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j < MAXN; j += i)
                isPrime[j] = false;
        }
    }
    for (int i = 2; i < MAXN; ++i)
        if (isPrime[i]) primes.push_back(i);
}

void buildBestGoldbach() {
    for (int e = 4; e <= MAXN - 1; e += 2) {
        int half = e / 2;
        for (int p = half; p >= 2; --p) {
            if (isPrime[p] && isPrime[e - p]) {
                bestGoldbach[e] = p;
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    buildBestGoldbach();

    int n;
    while (cin >> n && n != 0) {
        if (isPrime[n]) {
            cout << "1 " << n << "\n";
            continue;
        }

        if (n % 2 == 0) {                     // even, need 2 primes
            int p = bestGoldbach[n];
            int q = n - p;
            if (p > q) swap(p, q);
            cout << "2 " << p << ' ' << q << "\n";
            continue;
        }

        // n is odd and composite
        if (isPrime[n - 2]) {                 // 2 + (n-2)
            cout << "2 2 " << (n - 2) << "\n";
            continue;
        }

        // need three primes
        long long bestProd = -1;
        int bestA = 0, bestB = 0, bestC = 0;

        for (int a : primes) {
            if (a > n - 4) break;             // need at least 2 left
            int rem = n - a;                  // even
            int b = bestGoldbach[rem];
            int c = rem - b;
            long long prod = 1LL * a * b * c;
            if (prod > bestProd) {
                bestProd = prod;
                bestA = a; bestB = b; bestC = c;
            }
        }

        vector<int> ans = {bestA, bestB, bestC};
        sort(ans.begin(), ans.end());
        cout << "3 " << ans[0] << ' ' << ans[1] << ' ' << ans[2] << "\n";
    }
    return 0;
}
