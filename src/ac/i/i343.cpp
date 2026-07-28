#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<vector<ll>> a(n, vector<ll>(m));
        ll maxv = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                cin >> a[i][j];
                if (a[i][j] > maxv) maxv = a[i][j];
            }

        if (n < 2 || m < 2) {
            cout << 0 << '\n';
            continue;
        }

        // make rows the smaller dimension
        if (n > m) {
            vector<vector<ll>> b(m, vector<ll>(n));
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    b[j][i] = a[i][j];
            a.swap(b);
            swap(n, m);
        }

        const int L = (m + 63) >> 6;          // words per row

        auto possible = [&](ll X) -> bool {
            // build bitsets
            vector<vector<unsigned long long>> bits(n, vector<unsigned long long>(L, 0));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (a[i][j] >= X) {
                        bits[i][j >> 6] |= 1ULL << (j & 63);
                    }
                }
            }
            // check every pair of rows
            for (int i = 0; i < n; ++i) {
                for (int k = i + 1; k < n; ++k) {
                    int cnt = 0;
                    for (int w = 0; w < L; ++w) {
                        unsigned long long inter = bits[i][w] & bits[k][w];
                        if (inter) {
                            cnt += __builtin_popcountll(inter);
                            if (cnt >= 2) return true;
                        }
                    }
                }
            }
            return false;
        };

        ll low = 0, high = maxv + 1;          // [low, high)
        while (low + 1 < high) {
            ll mid = (low + high) >> 1;
            if (possible(mid))
                low = mid;
            else
                high = mid;
        }
        cout << low << '\n';
    }
    return 0;
}
