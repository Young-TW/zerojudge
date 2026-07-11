#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

const long long MOD = 1000000007LL;

struct Event {
    long long x;
    int type;      // 0 = update, 1 = query
    long long y;
    long long w;   // for update
    int id;        // for query
    int sign;      // for query
};

struct BIT {
    int n;
    vector<long long> tree;
    BIT(int n = 0) : n(n), tree(n + 1, 0) {}
    void init(int n_) { n = n_; tree.assign(n + 1, 0); }
    void add(int idx, long long val) {
        for (int i = idx; i <= n; i += i & -i) {
            tree[i] += val;
        }
    }
    long long query(int idx) {
        long long res = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            res += tree[i];
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, q;
    while (cin >> m >> q) {
        vector<Event> events;
        events.reserve(4 * m + 4 * q);
        vector<long long> ys;
        ys.reserve(2 * m + 2 * q);

        for (int i = 0; i < m; ++i) {
            long long u, d, l, r, k;
            cin >> u >> d >> l >> r >> k;
            events.push_back({u, 0, l, k, 0, 0});
            ys.push_back(l);
            events.push_back({u, 0, r + 1, -k, 0, 0});
            ys.push_back(r + 1);
            events.push_back({d + 1, 0, l, -k, 0, 0});
            ys.push_back(l);
            events.push_back({d + 1, 0, r + 1, k, 0, 0});
            ys.push_back(r + 1);
        }

        vector<long long> ans(q + 1, 0);
        for (int i = 1; i <= q; ++i) {
            long long u, d, l, r;
            cin >> u >> d >> l >> r;
            if (d >= 1 && r >= 1) {
                events.push_back({d, 1, r, 0, i, 1});
                ys.push_back(r);
            }
            if (u - 1 >= 1 && r >= 1) {
                events.push_back({u - 1, 1, r, 0, i, -1});
                ys.push_back(r);
            }
            if (d >= 1 && l - 1 >= 1) {
                events.push_back({d, 1, l - 1, 0, i, -1});
                ys.push_back(l - 1);
            }
            if (u - 1 >= 1 && l - 1 >= 1) {
                events.push_back({u - 1, 1, l - 1, 0, i, 1});
                ys.push_back(l - 1);
            }
        }

        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        int Y = ys.size();

        sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
            if (a.x != b.x) return a.x < b.x;
            return a.type < b.type; // updates before queries
        });

        BIT bit0(Y), bit1(Y), bit2(Y), bit3(Y);

        for (const auto& e : events) {
            int y_idx = lower_bound(ys.begin(), ys.end(), e.y) - ys.begin() + 1;
            if (e.type == 0) { // update
                long long w = e.w;
                long long w_mod = (w % MOD + MOD) % MOD;
                long long p = e.x;
                long long q = e.y;
                long long add0 = w_mod;
                long long add1 = (long long)((__int128)w_mod * q % MOD);
                long long add2 = (long long)((__int128)w_mod * p % MOD);
                long long add3 = (long long)((__int128)w_mod * p % MOD * q % MOD);
                bit0.add(y_idx, add0);
                bit1.add(y_idx, add1);
                bit2.add(y_idx, add2);
                bit3.add(y_idx, add3);
            } else { // query
                long long x = e.x;
                long long y = e.y;
                long long sum0 = bit0.query(y_idx) % MOD;
                long long sum1 = bit1.query(y_idx) % MOD;
                long long sum2 = bit2.query(y_idx) % MOD;
                long long sum3 = bit3.query(y_idx) % MOD;
                long long X = (x + 1) % MOD;
                long long Y_ = (y + 1) % MOD;
                __int128 val = 0;
                val += (__int128)X * Y_ % MOD * sum0 % MOD;
                val -= (__int128)X * sum1 % MOD;
                val -= (__int128)Y_ * sum2 % MOD;
                val += sum3;
                val %= MOD;
                if (val < 0) val += MOD;
                long long v = (long long)val;
                ans[e.id] = (ans[e.id] + e.sign * v) % MOD;
                if (ans[e.id] < 0) ans[e.id] += MOD;
            }
        }

        for (int i = 1; i <= q; ++i) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}
