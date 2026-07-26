#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n_ll, k_ll;
    while (cin >> n_ll >> k_ll) {
        int n = static_cast<int>(n_ll);
        int k = static_cast<int>(k_ll);
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        if (k > n) k = n;                 // window cannot be larger than the array
        if (k == 0) {                     // degenerate case, nothing to output
            cout << "\n\n";
            continue;
        }

        deque<int> dqMin, dqMax;
        vector<long long> mins, maxs;
        mins.reserve(n);
        maxs.reserve(n);

        for (int i = 0; i < n; ++i) {
            // maintain increasing deque for minima
            while (!dqMin.empty() && a[dqMin.back()] >= a[i]) dqMin.pop_back();
            dqMin.push_back(i);
            // maintain decreasing deque for maxima
            while (!dqMax.empty() && a[dqMax.back()] <= a[i]) dqMax.pop_back();
            dqMax.push_back(i);

            // discard indices that are out of the current window
            while (!dqMin.empty() && dqMin.front() <= i - k) dqMin.pop_front();
            while (!dqMax.empty() && dqMax.front() <= i - k) dqMax.pop_front();

            // window is ready
            if (i >= k - 1) {
                mins.push_back(a[dqMin.front()]);
                maxs.push_back(a[dqMax.front()]);
            }
        }

        // output minima
        for (size_t i = 0; i < mins.size(); ++i) {
            if (i) cout << ' ';
            cout << mins[i];
        }
        cout << '\n';
        // output maxima
        for (size_t i = 0; i < maxs.size(); ++i) {
            if (i) cout << ' ';
            cout << maxs[i];
        }
        cout << '\n';
    }
    return 0;
}
