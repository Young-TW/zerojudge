#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

inline double dist(const Point& a, const Point& b) {
    double dx = static_cast<double>(a.x - b.x);
    double dy = static_cast<double>(a.y - b.y);
    return sqrt(dx * dx + dy * dy);
}

/* ---------- DP for n <= 20 ---------- */
double solveDP(const vector<Point>& p) {
    const int n = (int)p.size();
    const int N = 1 << n;
    const double INF = 1e100;

    // distance matrix
    static double d[20][20];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            d[i][j] = dist(p[i], p[j]);

    vector<double> dp((size_t)N * n, INF);
    for (int i = 0; i < n; ++i) dp[(1 << i) * n + i] = 0.0;

    for (int mask = 1; mask < N; ++mask) {
        for (int last = 0; last < n; ++last) {
            if (!(mask & (1 << last))) continue;
            double cur = dp[mask * n + last];
            if (cur >= INF) continue;
            int remain = (~mask) & (N - 1);
            while (remain) {
                int nxt = __builtin_ctz(remain);
                int nmask = mask | (1 << nxt);
                double &ref = dp[nmask * n + nxt];
                double cand = cur + d[last][nxt];
                if (cand < ref) ref = cand;
                remain &= remain - 1;
            }
        }
    }

    double ans = INF;
    int full = N - 1;
    for (int i = 0; i < n; ++i) ans = min(ans, dp[full * n + i]);
    return ans;
}

/* ---------- Branch & Bound for n > 20 ---------- */
double mstWeight(const vector<vector<double>>& d,
                 const vector<int>& verts) {
    const int m = (int)verts.size();
    if (m <= 1) return 0.0;
    vector<double> minEdge(m, 1e100);
    vector<char> used(m, 0);
    minEdge[0] = 0.0;
    double total = 0.0;
    for (int i = 0; i < m; ++i) {
        int v = -1;
        for (int j = 0; j < m; ++j)
            if (!used[j] && (v == -1 || minEdge[j] < minEdge[v]))
                v = j;
        used[v] = 1;
        total += minEdge[v];
        for (int to = 0; to < m; ++to) if (!used[to]) {
            double w = d[verts[v]][verts[to]];
            if (w < minEdge[to]) minEdge[to] = w;
        }
    }
    return total;
}

void dfs(int cur, int visitedMask, double curLen,
         const vector<vector<double>>& d,
         int n, double& best,
         const vector<double>& minEdgeFrom,
         const vector<int>& order) {
    if (curLen >= best) return;
    if (visitedMask == (1 << n) - 1) {
        best = curLen;
        return;
    }

    // lower bound: current length + cheapest edge to remaining
    // + MST of remaining vertices
    double lb = curLen;
    double minEdge = 1e100;
    int remainMask = ((1 << n) - 1) ^ visitedMask;
    vector<int> remainVerts;
    for (int i = 0; i < n; ++i) if (remainMask & (1 << i)) {
        remainVerts.push_back(i);
        if (d[cur][i] < minEdge) minEdge = d[cur][i];
    }
    if (!remainVerts.empty()) lb += minEdge;
    if (remainVerts.size() > 1) lb += mstWeight(d, remainVerts);
    if (lb >= best) return;

    // try next vertices in order of increasing distance from cur
    vector<pair<double,int>> cand;
    for (int v : remainVerts) cand.emplace_back(d[cur][v], v);
    sort(cand.begin(), cand.end());

    for (auto &pr : cand) {
        int nxt = pr.second;
        dfs(nxt, visitedMask | (1 << nxt),
            curLen + d[cur][nxt],
            d, n, best, minEdgeFrom, order);
    }
}

double solveBB(const vector<Point>& p) {
    const int n = (int)p.size();
    vector<vector<double>> d(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            d[i][j] = dist(p[i], p[j]);

    // greedy nearest neighbour to obtain an initial upper bound
    double best = 1e100;
    for (int start = 0; start < n; ++start) {
        vector<char> used(n, 0);
        int cur = start;
        used[cur] = 1;
        double len = 0.0;
        for (int step = 1; step < n; ++step) {
            double bestDist = 1e100;
            int nxt = -1;
            for (int v = 0; v < n; ++v) if (!used[v]) {
                if (d[cur][v] < bestDist) {
                    bestDist = d[cur][v];
                    nxt = v;
                }
            }
            len += bestDist;
            cur = nxt;
            used[cur] = 1;
        }
        best = min(best, len);
    }

    // start DFS from every vertex
    for (int s = 0; s < n; ++s) {
        dfs(s, 1 << s, 0.0, d, n, best, vector<double>(), vector<int>());
    }
    return best;
}

/* ---------- main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<Point> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;

        double ans;
        if (n <= 20) ans = solveDP(p);
        else          ans = solveBB(p);

        ans += 1e-9;                     // avoid 1.999999 -> 2.00
        cout << fixed << setprecision(2) << ans << '\n';
    }
    return 0;
}
