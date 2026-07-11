#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 505;
vector<int> adj[MAXN];
int in_degree[MAXN];
bool visited[MAXN];
int n, m;

void dfs(int u, vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, component);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
        }
        memset(in_degree, 0, sizeof(in_degree));

        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            in_degree[b]++;
        }

        vector<vector<int>> components;
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= n; ++i) {
            if (!visited[i]) {
                vector<int> component;
                dfs(i, component);
                components.push_back(component);
            }
        }

        int k = 0;
        for (auto& component : components) {
            vector<int> zero_in_degree;
            for (int u : component) {
                if (in_degree[u] == 0) {
                    zero_in_degree.push_back(u);
                }
            }
            if (zero_in_degree.empty()) {
                k++;
            } else {
                k += zero_in_degree.size();
            }
        }

        cout << k << '\n';
    }

    return 0;
}
