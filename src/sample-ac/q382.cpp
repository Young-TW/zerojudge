#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    vector<int> pos(M + 1, 0);
    for (int i = 0; i < N; ++i) {
        pos[a[i]] = i + 1;
    }

    long long ans = 0;
    long long fact = 1;
    long long inv_fact = 1;

    for (int i = N - 1; i >= 0; --i) {
        int cnt = 0;
        for (int j = 1; j < a[i]; ++j) {
            if (pos[j] == 0 || pos[j] > i + 1) {
                cnt++;
            }
        }
        
        long long term = (long long)cnt * fact % MOD;
        ans = (ans + term) % MOD;

        if (i > 0) {
            fact = fact * (M - i) % MOD;
            inv_fact = inv_fact * power(M - i + 1, MOD - 2) % MOD;
        }
    }

    cout << ans << "\n";

    return 0;
}
