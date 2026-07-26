#include <bits/stdc++.h>
using namespace std;

struct Order {
    int start;
    int end;
    int profit;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        vector<Order> v(N);
        for (int i = 0; i < N; ++i) {
            int A, B, C;
            cin >> A >> B >> C;
            v[i].start = A;
            v[i].end   = A + B - 1;
            v[i].profit = C;
        }
        sort(v.begin(), v.end(), [](const Order& a, const Order& b) {
            if (a.end != b.end) return a.end < b.end;
            return a.start < b.start;
        });
        vector<int> ends(N);
        for (int i = 0; i < N; ++i) ends[i] = v[i].end;
        
        vector<long long> dp(N + 1, 0);   // dp[0] = 0
        for (int i = 1; i <= N; ++i) {
            int curStart = v[i - 1].start;
            // number of intervals with end < curStart
            int p = upper_bound(ends.begin(), ends.begin() + (i - 1),
                                curStart - 1) - ends.begin();
            long long take = dp[p] + v[i - 1].profit;
            dp[i] = max(dp[i - 1], take);
        }
        cout << "Case " << tc << ": " << dp[N] << "\n";
    }
    return 0;
}
