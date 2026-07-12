#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    while (cin >> n >> q) {
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + a[i];
        }

        vector<long long> sums;
        sums.reserve((long long)n * (n + 1) / 2);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                sums.push_back(pref[j] - pref[i]);
            }
        }

        sort(sums.begin(), sums.end());

        for (int i = 0; i < q; ++i) {
            long long t;
            cin >> t;
            auto it1 = lower_bound(sums.begin(), sums.end(), t);
            auto it2 = upper_bound(sums.begin(), sums.end(), t);
            cout << (it2 - it1) << "\n";
        }
    }

    return 0;
}
