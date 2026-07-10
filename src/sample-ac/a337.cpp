#include <cstdio>
#include <vector>
#include <map>
#include <array>
#include <algorithm>
using namespace std;

typedef long long ll;

struct LCT {
    vector<array<int,2>> ch;
    vector<int> fa;
    vector<ll> val;
    vector<int> mx;
    vector<char> rev;
    int n;

    void init(int nodes, const vector<ll>& vals) {
        n = nodes;
        ch.assign(n+1, {0,0});
        fa.assign(n+1, 0);
        val.assign(n+1, 0);
        mx.assign(n+1, 0);
        rev.assign(n+1, 0);
        for (int i = 0; i <= n; i++) { val[i] = vals[i]; mx[i] = i; }
    }

    bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

    void pushup(int x) {
        mx[x] = x;
        ll best = val[x];
        for (int d = 0; d < 2; d++) {
            int c = ch[x][d];
            if (c && val[mx[c]] > best) { best = val[mx[c]]; mx[x] = mx[c]; }
        }
    }

    void apply_rev(int x) { if(!x) return; swap(ch[x][0], ch[x][1]); rev[x] ^= 1; }

    void pushdown(int x) {
        if (rev[x]) {
            if (ch[x][0]) apply_rev(ch[x][0]);
            if (ch[x][1]) apply_rev(ch[x][1]);
            rev[x] = 0;
        }
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y];
        int d = (ch[y][1] == x);
        if (!isroot(y)) ch[z][ch[z][1]==y] = x;
        fa[x] = z;
        int c = ch[x][d^1];
        ch[y][d] = c; if (c) fa[c] = y;
        ch[x][d^1] = y; fa[y] = x;
        pushup(y); pushup(x);
    }

    void splay(int x) {
        static vector<int> stk;
        stk.clear();
        int y = x;
        while (!isroot(y)) { stk.push_back(y); y = fa[y]; }
        stk.push_back(y);
        for (int i = (int)stk.size()-1; i >= 0; i--) pushdown(stk[i]);
        while (!isroot(x)) {
            int y = fa[x], z = fa[y];
            if (!isroot(y)) {
                if ((ch[y][1]==x) ^ (ch[z][1]==y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }

    void access(int x) {
        for (int y = 0; x; y = x, x = fa[x]) {
            splay(x); ch[x][1] = y; pushup(x);
        }
    }

    void makeroot(int x) { access(x); splay(x); apply_rev(x); }

    int findroot(int x) {
        access(x); splay(x);
        while (ch[x][0]) { pushdown(x); x = ch[x][0]; }
        splay(x);
        return x;
    }

    void link(int x, int y) {
        makeroot(x);
        if (findroot(y) != x) fa[x] = y;
    }

    void cut(int x, int y) {
        makeroot(x);
        if (findroot(y) == x && fa[y] == x && ch[y][0] == 0) {
            ch[x][1] = 0; fa[y] = 0; pushup(x);
        }
    }

    int querymax(int x, int y) {
        makeroot(x); access(y); splay(y);
        return mx[y];
    }
};

int main() {
    int N, M, Q;
    while (scanf("%d %d %d", &N, &M, &Q) == 3) {
        vector<int> eu(M+1), ev(M+1);
        vector<ll> ew(M+1);
        for (int i = 1; i <= M; i++) {
            scanf("%d %d %lld", &eu[i], &ev[i], &ew[i]);
        }

        map<pair<int,int>, int> eid;
        for (int i = 1; i <= M; i++) {
            int a = eu[i], b = ev[i];
            if (a > b) swap(a, b);
            eid[{a, b}] = i;
        }

        vector<array<int,3>> ops(Q+1);
        vector<int> delTime(M+1, 0);
        vector<int> delEdge(Q+1, 0);

        for (int t = 1; t <= Q; t++) {
            int k, a, b;
            scanf("%d %d %d", &k, &a, &b);
            ops[t] = {k, a, b};
            if (k == 2) {
                int x = a, y = b;
                if (x > y) swap(x, y);
                auto it = eid.find({x, y});
                int id = it->second;
                delEdge[t] = id;
                delTime[id] = t;
            }
        }

        int total = N + M;
        const ll NEG = (ll)-1e18;
        vector<ll> vals(total+1, NEG);
        for (int i = 1; i <= M; i++) vals[N + i] = ew[i];

        LCT lct;
        lct.init(total, vals);

        auto addEdge = [&](int i) {
            int u = eu[i], v = ev[i], en = N + i;
            lct.makeroot(u);
            if (lct.findroot(v) != u) {
                lct.link(en, u);
                lct.link(en, v);
            } else {
                int m = lct.querymax(u, v);
                if (lct.val[m] > ew[i]) {
                    int j = m - N;
                    lct.cut(m, eu[j]);
                    lct.cut(m, ev[j]);
                    lct.link(en, u);
                    lct.link(en, v);
                }
            }
        };

        for (int i = 1; i <= M; i++) {
            if (delTime[i] == 0) addEdge(i);
        }

        vector<ll> ansForT(Q+1, 0);

        for (int t = Q; t >= 1; t--) {
            if (ops[t][0] == 1) {
                int a = ops[t][1], b = ops[t][2];
                if (a == b) {
                    ansForT[t] = 0;
                } else {
                    lct.makeroot(a);
                    if (lct.findroot(b) != a) {
                        ansForT[t] = 0;
                    } else {
                        int m = lct.querymax(a, b);
                        ansForT[t] = lct.val[m];
                    }
                }
            } else {
                int id = delEdge[t];
                addEdge(id);
            }
        }

        for (int t = 1; t <= Q; t++) {
            if (ops[t][0] == 1) printf("%lld\n", ansForT[t]);
        }
    }
    return 0;
}
