#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    long long s, e, w;
    int s_idx, e_idx;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        vector<Interval> intervals(n);
        vector<long long> times;
        for (int i = 0; i < n; ++i) {
            cin >> intervals[i].s >> intervals[i].e >> intervals[i].w;
            times.push_back(intervals[i].s);
            times.push_back(intervals[i].e);
        }
        
        sort(times.begin(), times.end());
        times.erase(unique(times.begin(), times.end()), times.end());
        
        auto getIdx = [&](long long val) {
            return lower_bound(times.begin(), times.end(), val) - times.begin();
        };
        
        for (int i = 0; i < n; ++i) {
            intervals[i].s_idx = getIdx(intervals[i].s);
            intervals[i].e_idx = getIdx(intervals[i].e);
        }
        
        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
            return a.e_idx < b.e_idx;
        });
        
        vector<long long> dp(times.size(), 0);
        
        int ptr = 0;
        for (int i = 0; i < times.size(); ++i) {
            if (i > 0) dp[i] = dp[i - 1];
            while (ptr < n && intervals[ptr].e_idx == i) {
                dp[i] = max(dp[i], dp[intervals[ptr].s_idx] + intervals[ptr].w);
                ptr++;
            }
        }
        
        cout << dp.back() << "\n";
    }
    return 0;
}
