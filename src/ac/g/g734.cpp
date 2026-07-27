#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long c;
    if (!(cin >> n >> c)) return 0;          // single test case
    vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) cin >> h[i];
    vector<int> d(n);                        // d[1..n-1], d[0] unused
    for (int i = 1; i <= n - 1; ++i) cin >> d[i];
    
    // prefix distances: pref[t] = sum_{k=1}^{t} d[k]
    vector<long long> pref(n, 0);
    for (int i = 1; i <= n - 1; ++i) pref[i] = pref[i - 1] + d[i];
    
    const long long INF = (1LL << 60);
    long long answer = INF;
    
    for (int H = 1; H <= 100; ++H) {
        int prev = -1;
        for (int i = 1; i <= n; ++i) {
            if (h[i] >= H) {
                if (prev != -1) {
                    int low = min(h[prev], h[i]);
                    long long width = pref[i - 1] - pref[prev - 1];
                    long long vol = 1LL * low * width;
                    if (vol >= c && vol < answer) answer = vol;
                }
                prev = i;
            }
        }
    }
    
    if (answer == INF) cout << -1 << '\n';
    else               cout << answer << '\n';
    return 0;
}
