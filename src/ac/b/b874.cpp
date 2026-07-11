#include <iostream>
#include <bitset>
#include <cstring>

using namespace std;

const int MAX_M = 10005;

int cnt[MAX_M];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int N, M;
        cin >> N >> M;
        
        if (M <= 0) {
            for (int i = 0; i < N; ++i) {
                long long x;
                cin >> x;
            }
            cout << "NO\n";
            continue;
        }

        if (M == 1) {
            for (int i = 0; i < N; ++i) {
                long long x;
                cin >> x;
            }
            if (N > 0) cout << "YES\n";
            else cout << "NO\n";
            continue;
        }

        memset(cnt, 0, sizeof(cnt));
        bool found_zero = false;
        for (int i = 0; i < N; ++i) {
            long long x;
            cin >> x;
            if (found_zero) continue;
            int r = (x % M + M) % M;
            if (r == 0) {
                found_zero = true;
            } else {
                cnt[r]++;
            }
        }

        if (found_zero) {
            cout << "YES\n";
            continue;
        }

        bitset<MAX_M> dp;
        bitset<MAX_M> mask;
        for (int i = 0; i < M; ++i) {
            mask[i] = 1;
        }
        dp[0] = 1;

        bool ok = false;
        for (int r = 1; r < M; ++r) {
            if (cnt[r] > 0) {
                int k = 1;
                while (cnt[r] >= k) {
                    cnt[r] -= k;
                    int shift = (1LL * k * r) % M;
                    if (shift == 0) {
                        ok = true;
                        break;
                    }
                    if (dp[M - shift]) {
                        ok = true;
                        break;
                    }
                    dp = (dp | ((dp << shift) | (dp >> (M - shift)))) & mask;
                    k <<= 1;
                }
                if (ok) break;
                if (cnt[r] > 0) {
                    int shift = (1LL * cnt[r] * r) % M;
                    if (shift == 0) {
                        ok = true;
                        break;
                    }
                    if (dp[M - shift]) {
                        ok = true;
                        break;
                    }
                    dp = (dp | ((dp << shift) | (dp >> (M - shift)))) & mask;
                }
                if (ok) break;
            }
        }

        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
