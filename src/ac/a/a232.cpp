#include <bits/stdc++.h>
using namespace std;

// NOI2010 Altitude: directed planar min-cut S(NW)->T(SE) via dual shortest path.

static int n;
static inline int cellNode(int r, int c) { return r * n + c + 1; } // r,c in [0,n-1]

// fast input
static char *inbuf;
static size_t inpos, inlen;
static inline long long readInt() {
    while (inpos < inlen && (inbuf[inpos] < '0' || inbuf[inpos] > '9') && inbuf[inpos] != '-') inpos++;
    bool neg = false;
    if (inpos < inlen && inbuf[inpos] == '-') { neg = true; inpos++; }
    long long v = 0;
    while (inpos < inlen && inbuf[inpos] >= '0' && inbuf[inpos] <= '9') { v = v * 10 + (inbuf[inpos] - '0'); inpos++; }
    return neg ? -v : v;
}

int main() {
    // read all stdin
    {
        vector<char> data;
        char tmp[1 << 16];
        size_t r;
        while ((r = fread(tmp, 1, sizeof(tmp), stdin)) > 0) data.insert(data.end(), tmp, tmp + r);
        inlen = data.size();
        inbuf = (char*)malloc(inlen + 1);
        memcpy(inbuf, data.data(), inlen);
        inpos = 0;
    }

    n = (int)readInt();
    int SRC = 0;                 // NE outer region
    int SNK = n * n + 1;         // SW outer region
    int V = n * n + 2;

    // CSR-ish adjacency using vectors
    vector<vector<pair<int,int>>> adj(V);
    long long totalArcs = 4LL * n * (n + 1);
    // reserve rough
    // (skip precise reservation)

    auto addArc = [&](int u, int w, int cap) {
        adj[u].push_back({w, cap});
    };

    // neighbor helpers with boundary mapping
    // horizontal road H(r,c): r in 0..n, c in 0..n-1. above=U (cell r-1,c) or SRC if r==0; below=D (cell r,c) or SNK if r==n
    auto Hup = [&](int r, int c) -> int { return (r == 0) ? SRC : cellNode(r - 1, c); };
    auto Hdn = [&](int r, int c) -> int { return (r == n) ? SNK : cellNode(r, c); };
    // vertical road V(r,c): r in 0..n-1, c in 0..n. left=L (cell r,c-1) or SNK if c==0; right=R (cell r,c) or SRC if c==n
    auto Vleft  = [&](int r, int c) -> int { return (c == 0) ? SNK : cellNode(r, c - 1); };
    auto Vright = [&](int r, int c) -> int { return (c == n) ? SRC : cellNode(r, c); };

    // Read groups. We need to store fWE,fEW per H and fNS,fSN per V because arcs use both.
    // But arcs can be added immediately per group since each dart is independent.

    // Group 1: W->E for H(r,c), order r=0..n, c=0..n-1. dart u=p(r,c)->p(r,c+1). left=U,right=D => arc U->D wt.
    for (int r = 0; r <= n; r++)
        for (int c = 0; c < n; c++) {
            int f = (int)readInt();
            addArc(Hup(r, c), Hdn(r, c), f);
        }
    // Group 2: N->S for V(r,c), order r=0..n-1, c=0..n. dart p(r,c)->p(r+1,c). left=R,right=L => arc R->L.
    for (int r = 0; r < n; r++)
        for (int c = 0; c <= n; c++) {
            int f = (int)readInt();
            addArc(Vright(r, c), Vleft(r, c), f);
        }
    // Group 3: E->W for H(r,c), order r=0..n,c=0..n-1. dart p(r,c+1)->p(r,c). left=D,right=U => arc D->U.
    for (int r = 0; r <= n; r++)
        for (int c = 0; c < n; c++) {
            int f = (int)readInt();
            addArc(Hdn(r, c), Hup(r, c), f);
        }
    // Group 4: S->N for V(r,c), order r=0..n-1,c=0..n. dart p(r+1,c)->p(r,c). left=L,right=R => arc L->R.
    for (int r = 0; r < n; r++)
        for (int c = 0; c <= n; c++) {
            int f = (int)readInt();
            addArc(Vleft(r, c), Vright(r, c), f);
        }

    // Dijkstra from SRC to SNK
    const long long INF = (long long)4e18;
    vector<long long> dist(V, INF);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    dist[SRC] = 0;
    pq.push({0, SRC});
    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        if (u == SNK) break;
        for (size_t i = 0; i < adj[u].size(); i++) {
            pair<int,int> &e = adj[u][i];
            long long nd = d + e.second;
            if (nd < dist[e.first]) {
                dist[e.first] = nd;
                pq.push({nd, e.first});
            }
        }
    }

    printf("%lld\n", dist[SNK] == INF ? 0LL : dist[SNK]);
    return 0;
}
