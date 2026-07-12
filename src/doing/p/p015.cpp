#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        int min_cycle = -1;

        // 對每個節點進行 BFS 尋找回到自己的最短路徑
        for (int start = 1; start <= n; ++start) {
            // dist[i] 記錄從 start 到 i 的距離，初始化為 -1
            vector<int> dist(n + 1, -1);
            queue<int> q;

            dist[start] = 0;
            q.push(start);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                // 如果當前距離已經大於等於目前找到的最小環長度，則不需要繼續探索這條路徑
                if (min_cycle != -1 && dist[u] >= min_cycle) {
                    continue;
                }

                for (int v : adj[u]) {
                    if (v == start) {
                        // 找到一個環
                        int cycle_len = dist[u] + 1;
                        if (min_cycle == -1 || cycle_len < min_cycle) {
                            min_cycle = cycle_len;
                        }
                    } else if (dist[v] == -1) {
                        // 如果還沒訪問過，則更新距離並加入隊列
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                }
            }
        }

        cout << min_cycle << "\n";
    }

    return 0;
}
