#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    long long L;
    while (cin >> N >> L) {
        vector<long long> pref(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            long long a; cin >> a;
            pref[i] = pref[i - 1] + a;
        }

        // 1. compute next[i]
        vector<int> nxt(N + 2, N + 1);          // nxt[N+1] = N+1
        int j = 1;
        for (int i = 1; i <= N; ++i) {
            if (j <= i) j = i + 1;
            while (j <= N && pref[j] - pref[i - 1] <= L) ++j;
            nxt[i] = j;                         // first index that would exceed L
        }
        nxt[N + 1] = N + 1;

        // 2. binary lifting table
        int LOG = 0;
        while ((1 << LOG) <= N + 1) ++LOG;      // LOG = ceil(log2(N+2))
        vector<vector<int>> up(LOG, vector<int>(N + 2));
        for (int i = 1; i <= N + 1; ++i) up[0][i] = nxt[i];
        for (int k = 1; k < LOG; ++k) {
            for (int i = 1; i <= N + 1; ++i) {
                up[k][i] = up[k - 1][ up[k - 1][i] ];
            }
        }

        // 3. answer each starting position
        for (int x = 1; x <= N; ++x) {
            int pos = x;
            int cnt = 0;
            for (int k = LOG - 1; k >= 0; --k) {
                int nxtPos = up[k][pos];
                if (nxtPos <= N) {
                    pos = nxtPos;
                    cnt += 1 << k;
                }
            }
            ++cnt; // the last box
            long long lastWeight = pref[N] - pref[pos - 1];
            cout << cnt << ' ' << lastWeight << '\n';
        }
    }
    return 0;
}
