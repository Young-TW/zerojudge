#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    if (!(cin >> N)) return 0;
    vector<long long> a(N);
    for (long long i = 0; i < N; ++i) cin >> a[i];

    if (N < 3) {
        long long ans = N * (N + 1) / 2;
        cout << ans << "\n";
        return 0;
    }

    vector<char> valley(N, 0);               // only indices 1 .. N-2 are used
    for (long long i = 1; i + 1 < N; ++i) {
        if (a[i - 1] > a[i] && a[i] < a[i + 1]) valley[i] = 1;
    }

    long long ans = 0;
    long long L = 0;                         // left border of current window
    int cnt = 0;                             // number of valleys inside [L..r]

    for (long long r = 0; r < N; ++r) {
        if (r - 1 >= 1 && valley[r - 1]) ++cnt;   // new valley may appear

        while (cnt > 0) {
            if (L + 1 <= N - 2 && valley[L + 1]) --cnt; // valley leaves
            ++L;
        }
        ans += r - L + 1;                     // all good sub‑arrays ending at r
    }

    cout << ans << "\n";
    return 0;
}
