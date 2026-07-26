#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250;                     // maximal number of different toys
const int WORDS = (MAXN + 63) / 64;       // = 4

using BitRow = array<unsigned long long, WORDS>;

struct Graph {
    int n;                                 // number of vertices (0 … n-1)
    vector<BitRow> nb;                     // adjacency matrix, symmetric
    Graph(int _n = 0) : n(_n), nb(_n) {
        for (int i = 0; i < _n; ++i) nb[i].fill(0ULL);
    }
};

/*---------------------------------------------------------------*/
/* degree of a vertex */
static inline int degree(const Graph &g, int v) {
    int d = 0;
    for (int w = 0; w < WORDS; ++w) d += __builtin_popcountll(g.nb[v][w]);
    return d;
}

/*---------------------------------------------------------------*/
/* remove a vertex (delete it and all incident edges) */
static void remove_vertex(Graph &g, int v) {
    for (int b = 0; b < WORDS; ++b) {
        unsigned long long mask = g.nb[v][b];
        while (mask) {
            unsigned long long low = mask & -mask;
            int t = __builtin_ctzll(low);
            int u = b * 64 + t;               // neighbour
            // clear the edge u‑v from u's row
            g.nb[u][v / 64] &= ~(1ULL << (v % 64));
            mask ^= low;
        }
    }
    for (int b = 0; b < WORDS; ++b) g.nb[v][b] = 0ULL;   // clear row of v
}

/*---------------------------------------------------------------*/
/* greedy maximal matching – returns its size (lower bound) */
static int greedy_matching(const Graph &g) {
    Graph tmp = g;                     // copy, we will destroy edges
    int match = 0;
    for (int i = 0; i < tmp.n; ++i) {
        for (int b = 0; b < WORDS; ++b) {
            unsigned long long mask = tmp.nb[i][b];
            while (mask) {
                unsigned long long low = mask & -mask;
                int t = __builtin_ctzll(low);
                int j = b * 64 + t;               // neighbour
                // match (i , j)
                ++match;
                remove_vertex(tmp, i);
                remove_vertex(tmp, j);
                // restart scanning from the beginning
                i = -1;   // will become 0 after ++i in outer loop
                goto next_edge;
            }
        }
    }
next_edge:
    return match;
}

/*---------------------------------------------------------------*/
/* repeatedly apply degree‑1 reduction, increasing cur */
static void degree_one_reduction(Graph &g, int &cur) {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int v = 0; v < g.n; ++v) {
            int deg = degree(g, v);
            if (deg == 1) {
                // find its unique neighbour
                int nbv = -1;
                for (int b = 0; b < WORDS; ++b) {
                    if (g.nb[v][b]) {
                        int t = __builtin_ctzll(g.nb[v][b]);
                        nbv = b * 64 + t;
                        break;
                    }
                }
                if (nbv == -1) continue; // should not happen
                ++cur;                     // neighbour forced into cover
                remove_vertex(g, nbv);     // delete neighbour (and its edges)
                // vertex v becomes isolated automatically
                changed = true;
                break;                     // restart scanning
            }
        }
    }
}

/*---------------------------------------------------------------*/
/* branch‑and‑bound search for minimum vertex cover */
static void dfs(const Graph &g, int cur, int &best) {
    if (cur >= best) return;                     // prune 1

    // check whether any edge remains
    bool hasEdge = false;
    for (int i = 0; i < g.n && !hasEdge; ++i) {
        for (int b = 0; b < WORDS; ++b) {
            if (g.nb[i][b]) { hasEdge = true; break; }
        }
    }
    if (!hasEdge) {                               // all edges covered
        best = cur;
        return;
    }

    // lower bound from greedy maximal matching
    int lb = greedy_matching(g);
    if (cur + lb >= best) return;                // prune 2

    // choose vertex of maximum degree
    int u = -1, maxDeg = -1;
    for (int i = 0; i < g.n; ++i) {
        int d = degree(g, i);
        if (d > maxDeg) { maxDeg = d; u = i; }
    }
    // find a neighbour v of u
    int v = -1;
    for (int b = 0; b < WORDS; ++b) {
        if (g.nb[u][b]) {
            int t = __builtin_ctzll(g.nb[u][b]);
            v = b * 64 + t;
            break;
        }
    }
    if (v == -1) return; // should not happen because we know an edge exists

    // branch 1 : take u
    {
        Graph g1 = g;
        remove_vertex(g1, u);
        dfs(g1, cur + 1, best);
    }
    // branch 2 : take v
    {
        Graph g2 = g;
        remove_vertex(g2, v);
        dfs(g2, cur + 1, best);
    }
}

/*---------------------------------------------------------------*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    while ( (cin >> m) && m != 0 ) {
        vector<pair<int,int>> wishes(m);
        vector<int> all;
        all.reserve(2*m);
        for (int i = 0; i < m; ++i) {
            int a,b; cin >> a >> b;
            wishes[i] = {a,b};
            all.push_back(a);
            all.push_back(b);
        }

        // compress toy numbers
        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());
        int n = (int)all.size();
        unordered_map<int,int> id;
        id.reserve(n*2);
        for (int i = 0; i < n; ++i) id[all[i]] = i;

        Graph g(n);
        int forced = 0;                     // toys forced because of loops

        for (auto &p : wishes) {
            int u = id[p.first];
            int v = id[p.second];
            if (u == v) {                   // loop
                ++forced;
                continue;
            }
            // set edge (undirected)
            g.nb[u][v/64] |= 1ULL << (v%64);
            g.nb[v][u/64] |= 1ULL << (u%64);
        }

        // degree‑1 reduction before the main search
        degree_one_reduction(g, forced);

        // after reduction, maybe no edges left
        bool anyEdge = false;
        for (int i = 0; i < g.n && !anyEdge; ++i)
            for (int b = 0; b < WORDS; ++b)
                if (g.nb[i][b]) { anyEdge = true; break; }

        int answer;
        if (!anyEdge) {
            answer = forced;
        } else {
            int best = g.n;                 // trivial upper bound
            dfs(g, forced, best);
            answer = best;
        }
        cout << answer << '\n';
    }
    return 0;
}
