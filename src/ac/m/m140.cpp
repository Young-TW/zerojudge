#include <bits/stdc++.h>
using namespace std;

using Interval = pair<int, int>;

bool feasible(int K, int need, const vector<Interval>& iv) {
    // intervals are already sorted by start
    multiset<int> active;               // end times of currently kept intervals
    int kept = 0;

    for (const auto& p : iv) {
        int s = p.first;
        int t = p.second;

        // remove intervals that already ended before day s
        while (!active.empty() && *active.begin() <= s) {
            active.erase(active.begin());
        }

        // try to keep the new interval
        active.insert(t);
        ++kept;

        // if capacity exceeded, discard the interval with the latest end
        if ((int)active.size() > K) {
            auto it = prev(active.end());   // largest end
            active.erase(it);
            --kept;
        }
    }
    return kept >= need;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<Interval> iv(N);
        for (int i = 0; i < N; ++i) {
            int s, t;
            cin >> s >> t;
            iv[i] = {s, t};
        }

        // sort by start (if tie, by end)
        sort(iv.begin(), iv.end(),
             [](const Interval& a, const Interval& b) {
                 if (a.first != b.first) return a.first < b.first;
                 return a.second < b.second;
             });

        int need = (N + 1) / 2;          // ceil(N/2)

        int lo = 1, hi = N, ans = N;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (feasible(mid, need, iv)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
