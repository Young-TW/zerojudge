#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Interval {
    int l, r;
    int len;
    bool operator<(const Interval& other) const {
        if (r != other.r) return r < other.r;
        return l < other.l;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, T;
    while (cin >> M >> T) {
        vector<Interval> intervals(T);
        for (int i = 0; i < T; ++i) {
            int S, E;
            cin >> S >> E;
            if (S > E) {
                swap(S, E);
            }
            intervals[i].l = S;
            intervals[i].r = E;
            intervals[i].len = E - S;
        }
        
        sort(intervals.begin(), intervals.end());
        
        vector<int> ends(T + 1);
        ends[0] = -1;
        for (int i = 1; i <= T; ++i) {
            ends[i] = intervals[i-1].r;
        }
        
        vector<int> dp(T + 1, 0);
        for (int i = 1; i <= T; ++i) {
            int l = intervals[i-1].l;
            int len = intervals[i-1].len;
            int idx = upper_bound(ends.begin(), ends.end(), l) - ends.begin() - 1;
            dp[i] = max(dp[i-1], dp[idx] + len);
        }
        
        cout << dp[T] << "\n";
    }
    
    return 0;
}
