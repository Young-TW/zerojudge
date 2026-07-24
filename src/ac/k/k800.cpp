#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

// 定義長整數，避免溢出
typedef long long ll;

const ll INF_LL = 1e18;
const int INF_INT = 1e9;

struct Edge {
    int to;
    int rev; // 反向邊在 adj[to] 中的索引
    ll cap;
    ll cost;
};

int main() {
    // 優化 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll C;
    if (!(cin >> n >> C)) return 0;

    vector<ll> a(n);
    ll sum_a = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum_a += a[i];
    }

    // 讀入成本矩陣
    vector<vector<ll>> c(n, vector<ll>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> c[i][j];
        }
    }

    // 步驟 1: Floyd-Warshall 預處理最短路徑成本
    // c[i][j] 表示從 i 移動 1 單位高度到 j 的最小成本
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (c[i][k] != INF_LL && c[k][j] != INF_LL) { // 雖然題目保證有值，但習慣性檢查
                     if (c[i][j] > c[i][k] + c[k][j]) {
                        c[i][j] = c[i][k] + c[k][j];
                    }
                }
            }
        }
    }

    // 計算供給和需求
    vector<ll> sup(n, 0);
    vector<ll> dem(n, 0);
    ll total_demand = 0;

    for (int i = 0; i < n; ++i) {
        if (a[i] > C) {
            sup[i] = a[i] - C;
        } else if (a[i] < C) {
            dem[i] = C - a[i];
            total_demand += dem[i];
        }
    }

    if (total_demand == 0) {
        cout << 0 << endl;
        return 0;
    }

    // 步驟 2: 建構最小費用流網絡
    // 節點: S=0, T=n+1, 衛星 1..n (對應原題 0..n-1)
    int S = 0;
    int T = n + 1;
    int V = n + 2;
    
    vector<vector<Edge>> graph(V);

    auto add_edge = [&](int u, int v, ll cap, ll cost) {
        Edge forward = {v, (int)graph[v].size(), cap, cost};
        Edge backward = {u, (int)graph[u].size(), 0, -cost};
        graph[u].push_back(forward);
        graph[v].push_back(backward);
    };

    // 添加邊
    for (int i = 0; i < n; ++i) {
        int node = i + 1;
        if (sup[i] > 0) {
            add_edge(S, node, sup[i], 0);
        }
        if (dem[i] > 0) {
            add_edge(node, T, dem[i], 0);
        }
        
        // 添加衛星之間的邊 (完全圖)
        // 注意：這裡只添加從 i 到 j 的邊，容量無限，成本為 c[i][j]
        // 為了減少邊數，我們可以只在需要的時候加？不，N=300, N^2=90000，可以全部加入
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            // 只有當 i 有供給潛力且 j 有需求潛力時才需要？
            // 不，在殘量網絡中，流向可能會改變，所以最好全部加上，或者動態處理
            // 但為了簡單，全部加上。容量設為 INF
            add_edge(node, j + 1, INF_LL, c[i][j]);
        }
    }

    // 步驟 3: Successive Shortest Path with Dijkstra and Potential
    ll min_cost = 0;
    ll flow_count = 0;
    
    vector<ll> h(V, 0); // Potential
    vector<ll> dist(V);
    vector<int> prevv(V);
    vector<int> preve(V);

    // 初始 potential 可以用 Bellman-Ford 或 SPFA 計算，但因為初始沒有負權邊（反向邊容量為 0，不可達）
    // 所以初始 h 全為 0 即可。第一次 Dijkstra 不會遇到負權。
    
    while (flow_count < total_demand) {
        // Dijkstra
        fill(dist.begin(), dist.end(), INF_LL);
        dist[S] = 0;
        
        // priority_queue: pair<distance, vertex>
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        pq.push({0, S});
        
        // 使用 vector<char> 代替 vector<bool> 避免 CE
        vector<char> visited(V, 0); 

        while (!pq.empty()) {
            ll d = pq.top().first;
            int v = pq.top().second;
            pq.pop();

            if (visited[v]) continue;
            visited[v] = 1;

            if (d > dist[v]) continue;

            for (int i = 0; i < graph[v].size(); ++i) {
                Edge &e = graph[v][i];
                if (e.cap > 0) {
                    // 調整後的成本
                    ll new_cost = e.cost + h[v] - h[e.to];
                    if (dist[e.to] > dist[v] + new_cost) {
                        dist[e.to] = dist[v] + new_cost;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }
        }

        if (dist[T] == INF_LL) {
            // 理論上不應該發生，因為題目保證有解
            break;
        }

        // 更新 Potential
        for (int v = 0; v < V; ++v) {
            if (dist[v] != INF_LL) {
                h[v] += dist[v];
            }
        }

        // 計算路徑上的最大流量
        ll d = total_demand - flow_count;
        int v = T;
        while (v != S) {
            int p = prevv[v];
            int idx = preve[v];
            d = min(d, graph[p][idx].cap);
            v = p;
        }

        flow_count += d;
        
        // 更新殘量圖並計算成本
        v = T;
        while (v != S) {
            int p = prevv[v];
            int idx = preve[v];
            
            // 累加成本：使用原始成本 (e.cost) 乘以流量
            // 注意：h 已經更新了，但我們可以直接用 e.cost 計算，因為 e.cost 是固定的
            // 或者用 h[T] - h[S] ? 
            // 在 Dijkstra 中，dist[T] 是調整後的成本之和。
            // 真實成本 = dist[T] (調整後) - h_old[S] + h_old[T] ?
            // 簡單起見，遍歷時直接加 e.cost * d
            // 但要注意反向邊的 cost 是負的，這裡我們是推流，所以是正向邊減容量，反向邊加容量
            // 我們只需要知道這條邊的單位成本是多少。
            // graph[p][idx].cost 就是單位成本。
            
            min_cost += d * graph[p][idx].cost;
            
            graph[p][idx].cap -= d;
            int rev_idx = graph[p][idx].rev;
            graph[v][rev_idx].cap += d;
            
            v = p;
        }
    }

    cout << min_cost << endl;

    return 0;
}
