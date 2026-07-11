#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
vector<int> rev_adj[MAXN];
bool visited[MAXN];
int order[MAXN];
int component[MAXN];
int n, m;

void dfs1(int u, int &idx) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v, idx);
        }
    }
    order[idx++] = u;
}

void dfs2(int u, int c) {
    component[u] = c;
    for (int v : rev_adj[u]) {
        if (component[v] == -1) {
            dfs2(v, c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
            rev_adj[i].clear();
            visited[i] = false;
            component[i] = -1;
        }

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            rev_adj[v].push_back(u);
        }

        int idx = 0;
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                dfs1(i, idx);
            }
        }

        int comp_count = 0;
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            if (component[u] == -1) {
                dfs2(u, comp_count++);
            }
        }

        if (comp_count == 1) {
            cout << "Yes\n";
        } else {
            int start_comp = component[1];
            vector<int> out_degree(comp_count, 0);
            
            for (int u = 1; u <= n; ++u) {
                for (int v : adj[u]) {
                    if (component[u] != component[v]) {
                        out_degree[component[u]]++;
                    }
                }
            }

            bool possible = true;
            for (int i = 0; i < comp_count; ++i) {
                if (i == start_comp) continue;
                if (out_degree[i] == 0) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}
