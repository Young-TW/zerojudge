#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int MAXM = 1000005;

int head[MAXN], nxt[2 * MAXM], to[2 * MAXM], wt[2 * MAXM], ecnt = 0;
int col[MAXN];
bool vis[MAXN];
int qq[MAXN];
int n, m;
long long g = 0; // gcd of all cycle constraints

inline void addEdge(int u, int v, int w) {
    to[++ecnt] = v; wt[ecnt] = w; nxt[ecnt] = head[u]; head[u] = ecnt;
}

// fast reader
inline int readInt() {
    int c = getchar_unlocked();
    while (c != '-' && (c < '0' || c > '9')) c = getchar_unlocked();
    int sgn = 1;
    if (c == '-') { sgn = -1; c = getchar_unlocked(); }
    int x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = getchar_unlocked(); }
    return x * sgn;
}

int main() {
    n = readInt(); m = readInt();
    for (int i = 0; i < m; i++) {
        int a = readInt(), b = readInt();
        addEdge(a, b, 1);
        addEdge(b, a, -1);
    }

    long long M = 0; // sum of chain spans over components (acyclic case)
    for (int s = 1; s <= n; s++) {
        if (vis[s]) continue;
        int hd = 0, tl = 0;
        qq[tl++] = s; vis[s] = true; col[s] = 0;
        int mx = 0, mn = 0;
        while (hd < tl) {
            int u = qq[hd++];
            if (col[u] > mx) mx = col[u];
            if (col[u] < mn) mn = col[u];
            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                if (!vis[v]) {
                    vis[v] = true;
                    col[v] = col[u] + wt[e];
                    qq[tl++] = v;
                } else {
                    long long d = (long long)col[u] + wt[e] - col[v];
                    if (d < 0) d = -d;
                    g = __gcd(g, d);
                }
            }
        }
        M += (long long)(mx - mn + 1);
    }

    if (g >= 3) {
        long long mink;
        bool found = false;
        for (long long d = 3; d * d <= g; d++) {
            if (g % d == 0) { mink = d; found = true; break; }
        }
        if (!found) {
            if (g % 2 == 0 && g / 2 >= 3) mink = g / 2;
            else mink = g;
        }
        printf("%lld %lld\n", g, mink);
    } else if (g == 0 && M >= 3) {
        printf("%lld 3\n", M);
    } else {
        printf("-1 -1\n");
    }
    return 0;
}
