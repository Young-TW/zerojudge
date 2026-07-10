#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> p, r;
    void init(int n) { p.assign(n, -1); r.assign(n, 0); }
    int find(int x) { while (p[x] >= 0) { if (p[p[x]] >= 0) p[x] = p[p[x]]; x = p[x]; } return x; }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[a] += p[b]; p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
    int count(int n) { int c = 0; for (int i = 0; i < n; i++) if (p[i] < 0) c++; return c; }
};

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        vector<tuple<long long,int,int>> e;
        e.reserve(m);
        for (int k = 0; k < m; k++) {
            int i, j; long long c;
            scanf("%d %d %lld", &i, &j, &c);
            e.push_back({c, i, j});
        }
        sort(e.begin(), e.end());
        DSU dsu; dsu.init(n);
        long long total = 0; int used = 0;
        for (auto &t : e) {
            long long c; int i, j;
            tie(c, i, j) = t;
            if (dsu.unite(i, j)) { total += c; used++; }
        }
        if (n > 0 && dsu.count(n) == 1) printf("%lld\n", total);
        else if (n == 1) printf("0\n");
        else printf("-1\n");
    }
    return 0;
}
