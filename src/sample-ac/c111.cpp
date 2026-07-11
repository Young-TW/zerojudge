#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N && N) {
        string line;
        getline(cin, line); // consume newline after N
        vector<set<int>> adj_set(N + 1);
        while (getline(cin, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) continue;
            if (line == "0") break;
            stringstream ss(line);
            int u, v;
            if (ss >> u) {
                while (ss >> v) {
                    adj_set[u].insert(v);
                    adj_set[v].insert(u);
                }
            }
        }
        vector<vector<int>> adj(N + 1);
        for (int i = 1; i <= N; ++i) {
            for (int v : adj_set[i]) {
                adj[i].push_back(v);
            }
        }

        vector<int> disc(N + 1, 0), low(N + 1, 0), parent(N + 1, -1);
        vector<bool> ap(N + 1, false);
        int time_counter = 0;

        function<void(int)> dfs = [&](int u) {
            int children = 0;
            disc[u] = low[u] = ++time_counter;
            for (int v : adj[u]) {
                if (!disc[v]) {
                    children++;
                    parent[v] = u;
                    dfs(v);
                    low[u] = min(low[u], low[v]);
                    if (parent[u] == -1 && children > 1) {
                        ap[u] = true;
                    }
                    if (parent[u] != -1 && low[v] >= disc[u]) {
                        ap[u] = true;
                    }
                } else if (v != parent[u]) {
                    low[u] = min(low[u], disc[v]);
                }
            }
        };

        for (int i = 1; i <= N; ++i) {
            if (!disc[i]) {
                dfs(i);
            }
        }

        int ans = 0;
        for (int i = 1; i <= N; ++i) {
            if (ap[i]) ans++;
        }
        cout << ans << "\n";
    }
    return 0;
}
