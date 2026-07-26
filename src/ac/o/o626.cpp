#include <bits/stdc++.h>
using namespace std;

struct File {
    int a, b, c, d;
    int id;               // original position
};

inline int getAttr(const File& f, int attr) {
    switch (attr) {
        case 1: return f.a;
        case 2: return f.b;
        case 3: return f.c;
        case 4: return f.d;
    }
    return 0; // never reached
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    while (cin >> N >> K) {
        vector<File> files(N);
        for (int i = 0; i < N; ++i) {
            cin >> files[i].a >> files[i].b >> files[i].c >> files[i].d;
            files[i].id = i;
        }

        vector<int> clicks(K);
        for (int i = 0; i < K; ++i) cin >> clicks[i];

        // 1. compress consecutive equal clicks
        struct Op { int attr; bool asc; };
        vector<Op> ops;
        for (int i = 0; i < K; ) {
            int attr = clicks[i];
            int cnt = 0;
            while (i < K && clicks[i] == attr) {
                ++cnt; ++i;
            }
            bool asc = (cnt % 2 == 1);          // odd → ascending
            ops.push_back({attr, asc});
        }

        // 2. comparator using ops in reverse order (most recent first)
        vector<Op> revOps = ops;
        reverse(revOps.begin(), revOps.end());

        auto cmp = [&](const File& x, const File& y) {
            for (const Op& op : revOps) {
                int vx = getAttr(x, op.attr);
                int vy = getAttr(y, op.attr);
                if (vx != vy) {
                    if (op.asc) return vx < vy;
                    else        return vx > vy;
                }
            }
            return x.id < y.id;   // stable tie‑breaker
        };

        sort(files.begin(), files.end(), cmp);

        for (const File& f : files) {
            cout << f.a << ' ' << f.b << ' ' << f.c << ' ' << f.d << '\n';
        }
    }
    return 0;
}
