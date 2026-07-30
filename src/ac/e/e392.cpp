// e392 規劃規劃找獎勵 — 自寫解
//
// 樹上所有 (無序) 節點對的路徑長 = 樹上唯一路徑長。求前 5N 短的路徑長,
// 依序輸出第 5k (k=1..N) 短者,不存在輸出 -1。
//
// 作法:重心分解 (centroid decomposition)
//   1. 先建立重心分解,對每個重心存下「整個子樹到重心的距離陣列(排序)」與
//      「各分枝到重心的距離陣列(排序)」。
//   2. countLE(x) = Σ_重心 [ pairs(comp,x) - Σ pairs(branch,x) ]  用雙指標 O(size)。
//   3. 二分搜尋最小 L 使 countLE(L) >= M (M = min(5N, 總對數))。
//   4. cntLess = countLE(L-1) < M。列舉所有距離 < L 的對(數量 < M < 5N)排序,
//      排名 cntLess+1..M 皆為值 L。據此回答第 5k 短。
//
// 所有走訪皆用顯式堆疊(避免鏈狀樹遞迴爆棧);計數用容斥(避免星狀樹合併 O(n^2))。
// 全部自行撰寫。

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
vector<vector<pair<int, ll>>> adj;
vector<char> removed;
vector<int> par, sz, visStamp;
int stampCnt = 0;

vector<vector<ll>> comps;             // 每個重心的整棵分量距離(排序)
vector<vector<vector<ll>>> branches;  // 每個重心各分枝距離(排序)

vector<int> compNodes;

// 收集 entry 所在分量並找重心
int findCentroidOf(int entry) {
    ++stampCnt;
    compNodes.clear();
    compNodes.push_back(entry);
    visStamp[entry] = stampCnt;
    par[entry] = -1;
    for (size_t i = 0; i < compNodes.size(); ++i) {
        int u = compNodes[i];
        for (auto &pr : adj[u]) {
            int v = pr.first;
            if (!removed[v] && visStamp[v] != stampCnt) {
                visStamp[v] = stampCnt;
                par[v] = u;
                compNodes.push_back(v);
            }
        }
    }
    int total = (int)compNodes.size();
    for (int u : compNodes) sz[u] = 1;
    for (int i = total - 1; i >= 1; --i) sz[par[compNodes[i]]] += sz[compNodes[i]];

    int u = entry, pc = -1;
    while (true) {
        int nxt = -1;
        for (auto &pr : adj[u]) {
            int v = pr.first;
            if (removed[v] || v == pc) continue;
            int s = (par[v] == u) ? sz[v] : total - sz[u];
            if (s > total / 2) { nxt = v; break; }
        }
        if (nxt == -1) break;
        pc = u;
        u = nxt;
    }
    return u;
}

void buildDecomposition() {
    comps.clear();
    branches.clear();
    vector<int> work;
    work.push_back(1);
    while (!work.empty()) {
        int entry = work.back();
        work.pop_back();
        if (removed[entry]) continue;
        int c = findCentroidOf(entry);

        vector<ll> comp;
        comp.push_back(0);                 // 重心到自己
        vector<vector<ll>> brs;

        for (auto &pr : adj[c]) {
            int nb = pr.first;
            ll w = pr.second;
            if (removed[nb]) continue;
            // 顯式堆疊蒐集此分枝到重心的距離
            vector<ll> br;
            vector<pair<int, ll>> st;      // (node, dist), parent 用單獨陣列避免重入
            // 用堆疊 (node, parent, dist)
            vector<array<ll, 3>> stk;
            stk.push_back({(ll)nb, (ll)c, w});
            while (!stk.empty()) {
                auto cur = stk.back();
                stk.pop_back();
                int node = (int)cur[0], p = (int)cur[1];
                ll d = cur[2];
                br.push_back(d);
                for (auto &pr2 : adj[node]) {
                    int v = pr2.first;
                    if (!removed[v] && v != p && v != c) {
                        stk.push_back({(ll)v, (ll)node, d + pr2.second});
                    }
                }
            }
            sort(br.begin(), br.end());
            for (ll d : br) comp.push_back(d);
            brs.push_back(move(br));
        }
        sort(comp.begin(), comp.end());
        comps.push_back(move(comp));
        branches.push_back(move(brs));

        removed[c] = 1;
        for (auto &pr : adj[c]) {
            int nb = pr.first;
            if (!removed[nb]) work.push_back(nb);
        }
    }
}

// 排序陣列中 i<j 且 a_i+a_j<=x 的對數
static inline ll pairsLE(const vector<ll> &a, ll x) {
    ll cnt = 0;
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        if (a[l] + a[r] <= x) { cnt += (r - l); ++l; }
        else --r;
    }
    return cnt;
}

ll countLE(ll x) {
    ll total = 0;
    for (size_t i = 0; i < comps.size(); ++i) {
        total += pairsLE(comps[i], x);
        for (auto &br : branches[i]) total -= pairsLE(br, x);
    }
    return total;
}

// 列出排序陣列中 i<j 且 a_i+a_j<=T 的所有和
static inline void listPairsLE(const vector<ll> &a, ll T, vector<ll> &out) {
    int n = (int)a.size();
    for (int i = 0; i < n; ++i) {
        ll rem = T - a[i];
        if (a[i] > rem) break;             // 2*a[i] > T,之後更大,無配對
        int hi = (int)(upper_bound(a.begin(), a.end(), rem) - a.begin()) - 1;
        for (int j = i + 1; j <= hi; ++j) out.push_back(a[i] + a[j]);
    }
}

// 蒐集所有距離 <= T 的對(去除同分枝),回傳其和
vector<ll> collectLE(ll T) {
    vector<ll> res;
    if (T < 0) return res;
    vector<ll> Lall, Lsame;
    for (size_t i = 0; i < comps.size(); ++i) {
        Lall.clear();
        Lsame.clear();
        listPairsLE(comps[i], T, Lall);
        for (auto &br : branches[i]) listPairsLE(br, T, Lsame);
        sort(Lall.begin(), Lall.end());
        sort(Lsame.begin(), Lsame.end());
        // 由 Lall 依值扣除 Lsame(Lsame 為 Lall 的子多重集),餘者為跨分枝對
        size_t a = 0, b = 0;
        while (a < Lall.size()) {
            if (b < Lsame.size() && Lall[a] == Lsame[b]) { ++a; ++b; }
            else { res.push_back(Lall[a]); ++a; }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N) {
        adj.assign(N + 1, {});
        removed.assign(N + 1, 0);
        par.assign(N + 1, 0);
        sz.assign(N + 1, 0);
        visStamp.assign(N + 1, 0);
        stampCnt = 0;

        ll sumEdge = 0;
        for (int i = 0; i < N - 1; ++i) {
            int a, b; ll c;
            cin >> a >> b >> c;
            adj[a].push_back({b, c});
            adj[b].push_back({a, c});
            sumEdge += c;
        }

        ll totalPairs = (ll)N * (N - 1) / 2;
        ll M = min(5LL * N, totalPairs);

        if (M == 0) {                         // N <= 1
            for (int k = 1; k <= N; ++k) {
                if (k > 1) cout << ' ';
                cout << -1;
            }
            cout << '\n';
            continue;
        }

        buildDecomposition();

        // 二分搜尋最小 L 使 countLE(L) >= M
        ll lo = 0, hi = sumEdge;
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (countLE(mid) >= M) hi = mid;
            else lo = mid + 1;
        }
        ll L = lo;

        ll cntLess = (L == 0) ? 0 : countLE(L - 1);
        vector<ll> less = collectLE(L - 1);
        sort(less.begin(), less.end());       // size == cntLess

        for (int k = 1; k <= N; ++k) {
            ll rank = 5LL * k;
            ll ans;
            if (rank > M) ans = -1;
            else if (rank <= (ll)less.size()) ans = less[rank - 1];
            else ans = L;
            if (k > 1) cout << ' ';
            cout << ans;
        }
        cout << '\n';
    }
    return 0;
}
