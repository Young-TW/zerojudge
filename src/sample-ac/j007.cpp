#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>

using namespace std;

const int INF = 2e9;

struct Interval {
    int l, r, id;
    bool operator<(const Interval& o) const {
        return l > o.l;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        vector<Interval> intervals;
        for (int i = 1; i <= n; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int l, r;
                cin >> l >> r;
                intervals.push_back({l, r, i});
            }
        }
        sort(intervals.begin(), intervals.end());
        
        vector<int> min_r(n + 1, INF);
        multiset<int> ms;
        for (int i = 1; i <= n; i++) {
            ms.insert(INF);
        }
        
        int ans_len = INF;
        int ans_L = -1, ans_R = -1;
        
        int K = intervals.size();
        int i = 0;
        while (i < K) {
            int L = intervals[i].l;
            while (i < K && intervals[i].l == L) {
                int id = intervals[i].id;
                int r = intervals[i].r;
                auto it = ms.find(min_r[id]);
                if (it != ms.end()) {
                    ms.erase(it);
                }
                if (r < min_r[id]) {
                    min_r[id] = r;
                }
                ms.insert(min_r[id]);
                i++;
            }
            int R = *ms.rbegin();
            if (R != INF) {
                int len = R - L + 1;
                if (len < ans_len || (len == ans_len && L < ans_L)) {
                    ans_len = len;
                    ans_L = L;
                    ans_R = R;
                }
            }
        }
        
        cout << ans_L << " " << ans_R << "\n";
    }
    return 0;
}
