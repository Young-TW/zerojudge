#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 100005;

int ch[MAXN][26];
int fa[MAXN];
bool isP[MAXN];
int strNode[MAXN];
int nodeCnt;
int strCnt;

int fl[MAXN]; // fail link
vector<int> failCh[MAXN];
int tin[MAXN], tout[MAXN], timer;

int N;
int bit[MAXN];

void bitadd(int i, int v) {
    for (; i <= N; i += i & (-i)) bit[i] += v;
}
int bitq(int i) {
    int s = 0;
    for (; i > 0; i -= i & (-i)) s += bit[i];
    return s;
}

struct Q { int x, id; };
vector<Q> qryAt[MAXN];
int ans[MAXN];

int fstk[MAXN], fidx[MAXN];
int tstk[MAXN], tidx[MAXN];

int main() {
    static char s[MAXN];
    if (scanf("%s", s) != 1) return 0;
    int len = (int)strlen(s);

    nodeCnt = 1;
    int cur = 0;
    fa[0] = 0;
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == 'B') {
            cur = fa[cur];
        } else if (c == 'P') {
            strCnt++;
            strNode[strCnt] = cur;
            isP[cur] = true;
        } else {
            int idx = c - 'a';
            if (!ch[cur][idx]) {
                ch[cur][idx] = nodeCnt;
                fa[nodeCnt] = cur;
                nodeCnt++;
            }
            cur = ch[cur][idx];
        }
    }

    // BFS build fail links
    static int q[MAXN];
    int qh = 0, qt = 0;
    for (int c = 0; c < 26; c++) {
        int v = ch[0][c];
        if (v) { fl[v] = 0; q[qt++] = v; }
    }
    while (qh < qt) {
        int u = q[qh++];
        for (int c = 0; c < 26; c++) {
            int v = ch[u][c];
            if (v) {
                int f = fl[u];
                while (f && ch[f][c] == 0) f = fl[f];
                fl[v] = ch[f][c];
                q[qt++] = v;
            }
        }
    }

    // fail tree
    for (int u = 1; u < nodeCnt; u++) {
        failCh[fl[u]].push_back(u);
    }

    // Euler tour on fail tree (iterative)
    timer = 0;
    fstk[0] = 0; fidx[0] = 0; int ftop = 1;
    tin[0] = ++timer;
    while (ftop > 0) {
        int u = fstk[ftop - 1];
        if (fidx[ftop - 1] < (int)failCh[u].size()) {
            int v = failCh[u][fidx[ftop - 1]];
            fidx[ftop - 1]++;
            tin[v] = ++timer;
            fstk[ftop] = v; fidx[ftop] = 0; ftop++;
        } else {
            tout[u] = timer;
            ftop--;
        }
    }
    N = timer;

    // read queries
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int ynode = strNode[y];
        qryAt[ynode].push_back(Q{x, i});
    }

    // DFS on trie (iterative), answering queries at P-nodes
    int ttop = 0;
    tstk[0] = 0; tidx[0] = 0; ttop = 1;
    bitadd(tin[0], 1);
    while (ttop > 0) {
        int u = tstk[ttop - 1];
        while (tidx[ttop - 1] < 26 && ch[u][tidx[ttop - 1]] == 0) tidx[ttop - 1]++;
        if (tidx[ttop - 1] < 26) {
            int v = ch[u][tidx[ttop - 1]];
            tidx[ttop - 1]++;
            bitadd(tin[v], 1);
            if (isP[v]) {
                for (size_t j = 0; j < qryAt[v].size(); j++) {
                    int xnode = strNode[qryAt[v][j].x];
                    ans[qryAt[v][j].id] = bitq(tout[xnode]) - bitq(tin[xnode] - 1);
                }
            }
            tstk[ttop] = v; tidx[ttop] = 0; ttop++;
        } else {
            bitadd(tin[u], -1);
            ttop--;
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
