#include <cstdio>
using namespace std;
typedef long long ll;

// For 2N-digit Good numbers: X = L*10^N + R, L and R each N digits (leading nonzero).
// L|X <=> L|R, so R = L*k. X = L*(10^N + k). R|X <=> L*k | L*(10^N+k) <=> k | 10^N.
// k <= 9 (since R <= 10^N-1, L >= 10^(N-1), so k = R/L <= 9).
// k | 10^N and k<=9 => k in {1,2,4,5,8} (8 only when N>=3).
// For each such k: count N-digit L with L*k also N-digit.
//   L in [10^(N-1), 10^N -1], L*k in [10^(N-1), 10^N -1].
//   Since k|10^N: B = floor((10^N-1)/k) = 10^N/k - 1.
//   count = B - 10^(N-1) + 1 = 10^N/k - 10^(N-1) = 10^(N-1)*(10-k)/k.
// Compute count mod M. count = 10^(N-1)*(10-k)/k, k divides 10^(N-1)*(10-k).
// Use: (a / k) mod m (k|a) = ((a mod (k*m)) / k) mod m.

ll modpow(ll base, ll e, ll mod) {
    if (mod == 1) return 0;
    ll r = 1 % mod;
    base %= mod;
    while (e) {
        if (e & 1) r = (__int128)r * base % mod;
        base = (__int128)base * base % mod;
        e >>= 1;
    }
    return r;
}

ll countK(int k, ll N, ll M) {
    // count = 10^(N-1) * (10 - k) / k, mod M
    ll kM = (ll)k * M;
    ll pow10 = modpow(10, N - 1, kM);          // 10^(N-1) mod (k*M)
    ll a = (__int128)pow10 * (10 - k) % kM;    // a mod (k*M), divisible by k
    ll cnt = a / k;
    cnt %= M;
    return cnt;
}

int main() {
    ll N, M;
    while (scanf("%lld %lld", &N, &M) == 2) {
        ll ans = 0;
        int KSET[5] = {1, 2, 4, 5, 8};
        // k | 10^N: 10^N = 2^N * 5^N. k=1 always; 2 needs N>=1; 4 needs N>=2; 5 needs N>=1; 8 needs N>=3.
        for (int i = 0; i < 5; i++) {
            int k = KSET[i];
            bool ok = false;
            if (k == 1) ok = true;
            else if (k == 2) ok = (N >= 1);
            else if (k == 4) ok = (N >= 2);
            else if (k == 5) ok = (N >= 1);
            else if (k == 8) ok = (N >= 3);
            if (!ok) continue;
            ans = (ans + countK(k, N, M)) % M;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
