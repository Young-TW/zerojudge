#include <bits/stdc++.h>
using namespace std;

struct Cloud {
    long long insert_time;   // Ti of insertion
    long long L0, R0;        // original segment [L0,R0]
    int dir;                 // -1 left, 1 right
    long long len;           // R0 - L0
};

long long LEN;   // sky length

// reflect position of a point after moving dt units from start p with direction d
static inline long long reflect_pos(long long p, int d, long long dt) {
    if (LEN == 0) return 0;
    long long period = 2LL * LEN;
    long long pos = p + (long long)d * dt;          // may be negative
    long long m = ((pos % period) + period) % period;
    if (m <= LEN) return m;
    return period - m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    if (!(cin >> n >> LEN)) return 0;
    unordered_map<int, Cloud> active;   // key: color
    vector<int> answers;
    for (long long i = 0; i < n; ++i) {
        int type;
        cin >> type;
        if (type == 1) {                 // insert
            long long Ti, Ci, Li, Ri;
            int Di;
            cin >> Ti >> Ci >> Li >> Ri >> Di;
            Cloud c;
            c.insert_time = Ti;
            c.L0 = Li;
            c.R0 = Ri;
            c.dir = Di;
            c.len = Ri - Li;
            active[(int)Ci] = c;
        } else if (type == 2) {          // query
            long long Ti, Lq, Rq;
            cin >> Ti >> Lq >> Rq;
            int cnt = 0;
            for (auto &kv : active) {
                const Cloud &c = kv.second;
                long long dt = Ti - c.insert_time;
                if (dt < 0) continue; // not yet inserted (should not happen)
                long long curL = reflect_pos(c.L0, c.dir, dt);
                long long curR = curL + c.len;
                if (curL <= Rq && curR >= Lq) ++cnt;
            }
            answers.push_back(cnt);
        } else if (type == 3) {          // delete
            long long Ti, Ci;
            cin >> Ti >> Ci;
            active.erase((int)Ci);
        }
    }
    for (int x : answers) cout << x << '\n';
    return 0;
}
