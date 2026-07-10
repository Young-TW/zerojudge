#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll MOD = 100000007;

ll modpow(ll a, ll e, ll m) {
    ll r = 1 % m;
    a %= m; if (a < 0) a += m;
    while (e > 0) {
        if (e & 1) r = r * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return r;
}

ll inv(ll a) {
    return modpow(a, MOD - 2, MOD);
}

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        ll A[12][12];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                ll x;
                scanf("%lld", &x);
                x %= MOD;
                if (x < 0) x += MOD;
                A[i][j] = x;
            }
        ll det = 1 % MOD;
        bool singular = false;
        for (int col = 0; col < N; col++) {
            int pivot = -1;
            for (int r = col; r < N; r++) {
                if (A[r][col] != 0) { pivot = r; break; }
            }
            if (pivot == -1) { singular = true; break; }
            if (pivot != col) {
                for (int c = 0; c < N; c++) swap(A[pivot][c], A[col][c]);
                det = (MOD - det) % MOD;
            }
            ll iv = inv(A[col][col]);
            for (int r = col + 1; r < N; r++) {
                ll factor = A[r][col] * iv % MOD;
                if (factor == 0) continue;
                for (int c = col; c < N; c++) {
                    A[r][c] = (A[r][c] - factor * A[col][c] % MOD + MOD) % MOD;
                }
            }
            det = det * A[col][col] % MOD;
        }
        if (singular) det = 0;
        printf("%lld\n", det % MOD);
    }
    return 0;
}
