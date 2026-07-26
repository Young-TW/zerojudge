#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128  = __int128_t;

struct Group {
    int64 d;   // deadline
    int64 y;   // length (processing time)
    int64 x;   // multiplicity
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<Group> g;
        g.reserve(n);
        for (int i = 0; i < n; ++i) {
            int64 x, y, d;
            cin >> x >> y >> d;
            g.push_back({d, y, x});
        }
        sort(g.begin(), g.end(),
             [](const Group& a, const Group& b) { return a.d < b.d; });

        map<int64, int64> keep;          // processing time -> count
        i128 total = 0;                  // total processing time of kept jobs
        int64 answer = 0;                // total number of kept jobs

        for (const auto& cur : g) {
            int64 d = cur.d;
            int64 y = cur.y;
            int64 x = cur.x;

            if (y == 0) {                // zero‑length programs are always doable
                answer += x;
                continue;
            }

            total += (i128)x * y;
            answer += x;
            keep[y] += x;

            while (total > d) {
                auto it = prev(keep.end());          // largest processing time
                int64 t = it->first;
                int64 cnt = it->second;

                i128 excess = total - d;              // how much time we must save
                i128 need128 = (excess + t - 1) / t;   // ceil(excess / t)
                int64 need = (need128 > (i128)cnt) ? cnt : (int64)need128;

                total -= (i128)need * t;
                answer -= need;

                if (need == cnt)
                    keep.erase(it);
                else
                    it->second = cnt - need;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
