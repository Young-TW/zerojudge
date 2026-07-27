#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long m, n;
    while (cin >> m >> n) {
        vector<string> a(n);
        for (long long i = 0; i < n; ++i) cin >> a[i];

        if (m == 0 || m > n) {
            cout << 0 << '\n';
            continue;
        }

        unordered_map<string, int> cnt;
        cnt.reserve(static_cast<size_t>(m * 2));
        long long distinct = 0;          // number of colours with count > 0
        long long answer   = 0;

        for (long long i = 0; i < n; ++i) {
            // add a[i]
            auto it = cnt.find(a[i]);
            if (it == cnt.end()) {
                cnt.emplace(a[i], 1);
                ++distinct;
            } else {
                if (it->second == 0) ++distinct;
                ++(it->second);
            }

            // remove a[i-m] if window size exceeded m
            if (i >= m) {
                const string &old = a[i - m];
                auto itOld = cnt.find(old);
                --(itOld->second);
                if (itOld->second == 0) --distinct;
            }

            // window of exact size m is ready
            if (i >= m - 1 && distinct == m) ++answer;
        }

        cout << answer << '\n';
    }
    return 0;
}
