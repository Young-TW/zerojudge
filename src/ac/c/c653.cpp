#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        long long N;
        int Q;
        cin >> N >> Q;
        struct Op { long long L, R; int D; };
        vector<Op> ops(Q);
        vector<long long> pts;
        pts.reserve(2 * Q + 4);
        pts.push_back(1);
        pts.push_back(N + 1);
        for (int i = 0; i < Q; ++i) {
            long long L, R; int D;
            cin >> L >> R >> D;
            ops[i] = {L, R, D};
            if (D == 1) {
                pts.push_back(L);
                if (R + 1 <= N) pts.push_back(R + 1);
            }
        }
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        int M = (int)pts.size();                 // number of points
        vector<char> diff(M, 0);                 // xor‑difference array
        for (const auto &op : ops) {
            if (op.D == 0) continue;
            int l = lower_bound(pts.begin(), pts.end(), op.L) - pts.begin();
            long long rp1 = op.R + 1;
            if (rp1 > N) rp1 = N + 1;
            int r = lower_bound(pts.begin(), pts.end(), rp1) - pts.begin();
            diff[l] ^= 1;
            diff[r] ^= 1;
        }
        long long odd = 0;
        char cur = 0;
        for (int i = 0; i < M - 1; ++i) {
            cur ^= diff[i];
            if (cur) {
                odd += pts[i + 1] - pts[i];
            }
        }
        long long ans = llabs(2 * odd - N);
        cout << ans << '\n';
    }
    return 0;
}
