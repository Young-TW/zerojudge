#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int n;
vector<int> idv;
vector<vector<int>> adj;
vector<int> disc, low;
vector<bool> visited;
int timer;
int articulationCount;

void dfs(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;
    int children = 0;
    bool isArt = false;
    for (int v : adj[u]) {
        if (!visited[v]) {
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (parent != -1 && low[v] >= disc[u]) {
                isArt = true;
            }
        } else if (v != parent) {
            low[u] = min(low[u], disc[v]);
        }
    }
    if (parent == -1 && children > 1) {
        isArt = true;
    }
    if (isArt) articulationCount++;
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        if (scanf("%d", &n) != 1) break;
        idv.assign(n, 0);
        for (int i = 0; i < n; i++) scanf("%d", &idv[i]);
        adj.assign(n, {});
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (idv[i] > 1 && idv[j] > 1) {
                    int a = idv[i], b = idv[j];
                    while (b) { int t = a % b; a = b; b = t; }
                    if (a > 1) {
                        adj[i].push_back(j);
                        adj[j].push_back(i);
                    }
                }
            }
        }
        visited.assign(n, false);
        disc.assign(n, 0);
        low.assign(n, 0);
        timer = 0;
        articulationCount = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) dfs(i, -1);
        }
        printf("%d\n", articulationCount);
    }
    return 0;
}
