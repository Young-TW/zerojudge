#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using uint64 = unsigned long long;

uint64 solve(int64 N, int64 M) {
    if (N < M) return 0;
    if (M == 0) return 0;               // safety
    map<int64, uint64> mp;
    mp[N] = 1;

    int64 limit = 2 * M;                // split while size >= limit
    while (true) {
        if (mp.empty()) break;
        auto it = prev(mp.end());       // largest key
        if (it->first < limit) break;  // no more splittable pieces
        int64 s = it->first;
        uint64 cnt = it->second;
        mp.erase(it);
        int64 a = s / 2;
        int64 b = s - a;                // ceil
        mp[a] += cnt;
        mp[b] += cnt;
    }

    uint64 ans = 0;
    for (const auto &p : mp) {
        if (p.first >= M) ans += p.second;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 N, M;
    while (cin >> N >> M) {
        cout << solve(N, M) << '\n';
    }
    return 0;
}
