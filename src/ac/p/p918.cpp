#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N, M;
    while (cin >> N >> M) {
        unordered_map<long long, long long> have;
        have.reserve(N * 2);
        for (long long i = 0; i < N; ++i) {
            long long x; cin >> x;
            ++have[x];
        }

        unordered_map<long long, long long> need;
        need.reserve(1024);
        long long total_need = 0;
        for (long long i = 0; i < M; ++i) {
            long long k; cin >> k;
            total_need += k;
            for (long long j = 0; j < k; ++j) {
                long long t; cin >> t;
                ++need[t];
            }
        }

        long long extra = 0;
        for (const auto &p : need) {
            long long have_cnt = 0;
            auto it = have.find(p.first);
            if (it != have.end()) have_cnt = it->second;
            if (p.second > have_cnt) extra += p.second - have_cnt;
        }

        long long left = N + extra - total_need;
        cout << extra << ' ' << left << "\n";
    }
    return 0;
}
