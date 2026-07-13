#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    while (cin >> n) {
        string s;
        if (!(cin >> s)) break;
        int N = (int)n;
        const ull base = 1315423911ULL; // large odd base
        vector<ull> powb(N + 1), h(N + 1);
        powb[0] = 1;
        for (int i = 1; i <= N; ++i) powb[i] = powb[i - 1] * base;
        h[0] = 0;
        for (int i = 0; i < N; ++i) h[i + 1] = h[i] * base + (ull)(s[i] + 1);

        auto getHash = [&](int l, int r) -> ull { // [l, r)
            return h[r] - h[l] * powb[r - l];
        };

        int bestK = 0;
        int bestLen = 0;
        string bestStr;

        for (int L = 1; L <= N; ++L) {
            for (int i = 0; i + L <= N; ++i) {
                int k = 1;
                while (i + (k + 1) * L <= N &&
                       getHash(i, i + L) == getHash(i + k * L, i + (k + 1) * L)) {
                    ++k;
                }
                if (k > bestK ||
                    (k == bestK && (L > bestLen ||
                                    (L == bestLen && s.substr(i, L) < bestStr)))) {
                    bestK = k;
                    bestLen = L;
                    bestStr = s.substr(i, L);
                }
            }
        }

        cout << bestStr << "\n" << bestK << "\n";
    }
    return 0;
}
