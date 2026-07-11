#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 505;
int n, m;
int matchR[MAXN];
bool visited[MAXN];
vector<int> adj[MAXN];

bool dfs(int u) {
    for (size_t i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (!visited[v]) {
            visited[v] = true;
            if (matchR[v] == 0 || dfs(matchR[v])) {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
        }
        memset(matchR, 0, sizeof(matchR));
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }
        int matching = 0;
        for (int i = 1; i <= n; ++i) {
            memset(visited, false, sizeof(visited));
            if (dfs(i)) {
                matching++;
            }
        }
        cout << n - matching << "\n";
    }
    return 0;
}
