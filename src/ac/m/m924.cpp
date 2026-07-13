#include <iostream>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 10015;

long long catalan[MAXN];
long long inv[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    inv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }

    catalan[0] = 1;
    for (int i = 0; i < MAXN - 1; i++) {
        catalan[i + 1] = catalan[i] * 2 % MOD * (2 * i + 1) % MOD * inv[i + 2] % MOD;
    }

    int n;
    while (cin >> n) {
        cout << catalan[n] << "\n";
    }

    return 0;
}
