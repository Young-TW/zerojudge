#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 105;
vector<int> adj[MAXN];
int dfn[MAXN], low[MAXN], dfs_clock;
int sccno[MAXN], scc_cnt;
int stk[MAXN], top;
bool instk[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++dfs_clock;
    stk[++top] = u;
    instk[u] = true;
    for (size_t i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do {
            v = stk[top--];
            instk[v] = false;
            sccno[v] = scc_cnt;
        } while (v != u);
    }
}

void init(int n) {
    for (int i = 0; i <= 2 * n + 1; ++i) {
        adj[i].clear();
    }
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(sccno, 0, sizeof(sccno));
    memset(instk, 0, sizeof(instk));
    dfs_clock = scc_cnt = top = 0;
}

int get_node(const string& s) {
    int num = 0;
    for (size_t i = 1; i < s.size(); ++i) {
        num = num * 10 + (s[i] - '0');
    }
    if (s[0] == 'm') {
        return 2 * num;
    } else {
        return 2 * num + 1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int K;
    while (cin >> K) {
        while (K--) {
            int n, m;
            cin >> n >> m;
            init(n);
            for (int i = 0; i < m; ++i) {
                string a, b;
                cin >> a >> b;
                int u = get_node(a);
                int v = get_node(b);
                adj[u ^ 1].push_back(v);
                adj[v ^ 1].push_back(u);
            }
            for (int i = 2; i <= 2 * n + 1; ++i) {
                if (!dfn[i]) {
                    tarjan(i);
                }
            }
            bool ok = true;
            for (int i = 1; i <= n; ++i) {
                if (sccno[2 * i] == sccno[2 * i + 1]) {
                    ok = false;
                    break;
                }
            }
            cout << (ok ? "GOOD" : "BAD") << "\n";
        }
    }
    return 0;
}
