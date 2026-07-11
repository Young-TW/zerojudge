#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const long long INF_LL = numeric_limits<long long>::max();

struct Edge {
    int to;
    int weight;
    int id; // 用於區分多重邊，雖然本題主要靠字典序處理
};

// Dijkstra 狀態
struct State {
    long long dist;
    int u;
    vector<int> path; // 儲存路徑以比較字典序

    // 優先隊列需要反向比較 (最小堆)
    bool operator>(const State& other) const {
        if (dist != other.dist) {
            return dist > other.dist;
        }
        // 距離相同時，比較路徑的字典序
        // 我們希望字典序小的優先，所以如果 this->path > other.path 則返回 true (排在後面)
        return path > other.path;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, T;
    if (!(cin >> N >> M >> T)) return 0;

    vector<int> C(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> C[i];
    }

    // 鄰接表：adj[u] 包含 {v, w, original_index}
    // 為了處理字典序，我們在建立圖的時候需要特別注意
    // 題目要求：如果多條最短路徑時間相同，選擇字典序最小的路線。
    // 路線的字典序定義為經過的節點序列。例如 7->3->6->1 優於 7->5->1。
    // 這意味著在每一步選擇下一個節點時，如果累積距離相同，應該優先選擇節點編號較小的？
    // 不完全是。Dijkstra 擴展時，如果從不同前驅到達同一個點距離相同，我們要保留路徑字典序較小的那個。
    
    vector<vector<pair<int, int>>> adj(N + 1); // {neighbor, weight}
    // 由於輸入可能有多重邊，且題目提到 "路徑索引較小"，但通常這類題目若無明確給出邊的 ID 比較規則
    // 而只說 "訪問田地 7, 3, 6, 1 優於 7, 5, 1"，這純粹是節點序列的字典序。
    // 如果有兩條邊連接相同的兩個點且權重相同，走哪一條對節點序列沒影響，除非題目隱含邊的編號也要考慮。
    // 重新讀題："如果兩條路線的路徑在字典序上相同，則優先選擇路徑索引較小的那條"
    // 這句話有點奇怪。通常節點序列不同，字典序就不同了。只有當節點序列完全一樣時（例如多重邊），才比邊索引。
    // 但在本題中，節點序列決定了路徑。如果節點序列一樣，代表經過的點一樣。
    // 讓我們假設標準的節點序列字典序比較即可。若有平行邊，選哪條對節點序列無影響，但可能影響 "路徑索引"。
    // 不過，對於計算總時間和捷徑效果，只要節點序列確定，距離就確定。
    // 這裡我們先專注於找出每個點到 1 的最短路徑及其節點序列。

    // 為了高效處理字典序，我們不能在 Dijkstra 的 priority_queue 中直接存整個 vector<int> path，因為 N=10000 會 MLE/TLE。
    // 技巧：在 Dijkstra 放鬆邊時，如果發現新的距離等於當前最短距離，我們需要比較路徑的字典序。
    // 但比較完整路徑太慢。
    // 觀察：最短路徑樹 (SPT)。如果距離相同，我們要選字典序最小的路徑。
    // 這等同於在構建 SPT 時，對於每個節點 v，選擇一個前驅 p，使得 dist[p] + w(p,v) 最小，且在距離相同時，路徑 ...->p->v 的字典序最小。
    // 由於路徑是從 v 回溯到 1，字典序比較是從起點開始比。
    // 這是一個經典問題：求最短路徑中字典序最小的路徑。
    // 方法：先跑一次普通 Dijkstra 求出所有點到 1 的最短距離 dist[v]。
    // 然後，我們可以從 1 開始 BFS/DFS 構建最短路徑樹？不，因為我们要的是從任意點 v 走到 1 的路徑。
    // 路徑方向是 v -> ... -> 1。字典序比較的是序列 (v, next, ..., 1)。
    // 所以要讓 v 之後的節點盡量小。
    
    // 修正策略：
    // 1. 計算所有點到 1 的最短距離 dist[v]。這可以用反向圖跑 Dijkstra (從 1 出發到所有點) 得到，因為邊是雙向的，所以 dist[v] 就是 v 到 1 的最短距離。
    // 2. 確定每個點 v 在最短路徑上的下一個節點 next_node[v]。
    //    對於點 v，候選下一個節點 u 必須滿足：dist[v] == weight(v, u) + dist[u]。
    //    在這些候選 u 中，我們要選哪一個？
    //    路徑是 v -> u -> ... -> 1。
    //    比較兩條路徑 P1: v -> u1 -> ... 和 P2: v -> u2 -> ...
    //    首先比較 u1 和 u2。如果 u1 < u2，則 P1 字典序較小（因為第一個元素 v 相同，第二個 u1 < u2）。
    //    如果 u1 == u2，則比較後續路徑。
    //    這暗示我們應該貪心地選擇最小的 u？
    //    是的，只要 u 在最短路徑上 (即 dist[v] == w(v,u) + dist[u])，那麼選擇最小的 u 就能保證當前步字典序最小。
    //    那後續呢？如果 u1 < u2，不管後續如何，v->u1... 一定小於 v->u2...。
    //    所以策略很簡單：對於每個 v，在所有滿足最短路條件的鄰居 u 中，選擇編號最小的 u 作為 next_node[v]。
    //    這樣構出來的路徑一定是字典序最小的最短路徑。
    //    證明：假設有兩條最短路徑，第一條第二步是 u1，第二條是 u2，且 u1 < u2。則第一條字典序較小。
    //    如果 u1 == u2，則問題歸約為從 u1 開始的子問題。由數學歸納法，每次選最小的鄰居即可。

    // Step 1: 計算所有點到 1 的最短距離
    // 圖是雙向的，所以從 1 開始跑 Dijkstra 即可得到所有點到 1 的最短距離。
    vector<vector<pair<int, int>>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<long long> dist(N + 1, INF_LL);
    dist[1] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // Step 2: 為每個點 v (v != 1) 確定 next_node[v]
    // next_node[v] 是 v 在最短路徑上走向 1 的下一個點。
    // 條件：dist[v] == w(v, u) + dist[u]，且 u 的編號最小。
    vector<int> next_node(N + 1, -1);
    for (int v = 1; v <= N; ++v) {
        if (v == 1) continue;
        int best_u = -1;
        for (auto& edge : graph[v]) {
            int u = edge.first;
            int w = edge.second;
            if (dist[u] != INF_LL && dist[v] == (long long)w + dist[u]) {
                if (best_u == -1 || u < best_u) {
                    best_u = u;
                }
            }
        }
        next_node[v] = best_u;
    }

    // 現在我們可以計算原始的總行走時間
    long long original_total_time = 0;
    for (int i = 1; i <= N; ++i) {
        if (C[i] > 0) {
            if (dist[i] == INF_LL) {
                // 題目說每塊田地都可以到達穀倉，所以這情況不會發生
                continue;
            }
            original_total_time += (long long)C[i] * dist[i];
        }
    }

    // Step 3: 評估捷徑
    // 捷徑從 1 連接到某個點 X，長度為 T。
    // 對於一頭在 i 的牛，原本路徑是 i -> ... -> 1，距離 dist[i]。
    // 有了捷徑 (1, X, T)，牛可以在路徑上的任何一點 k 發現這條捷徑嗎？
    // 題目描述："如果一頭牛在去牛棚的路上偶然發現了這條捷徑... 她就會走捷徑"
    // 捷徑是連接 1 和 X 的。牛是從 i 往 1 走。
    // 牛只有在到達 X 點時，才能使用這條捷徑直接飛到 1 (耗時 T)。
    // 或者，牛是否可以在路徑上其他點轉去 X？
    // 題目說："否則，即使捷徑可以縮短行走時間，她也會繼續走她平常的路線。"
    // 這句關鍵："偶然發現了這條捷徑"。這暗示牛必須經過捷徑的端點才能使用它。
    // 捷徑端點是 1 和 X。牛終點是 1。所以牛只有在經過 X 時才能使用捷徑 (X -> 1, 耗時 T)。
    // 如果牛原本的路徑不經過 X，她就無法 "偶然發現" 捷徑，因此不會特意繞道去 X。
    // 所以，對於位於 i 的牛，如果 X 在她原本的最短路徑 (字典序最小那條) 上，
    // 則新路徑可能是：i -> ... -> X -> (捷徑) -> 1。
    // 新距離 = dist(i, X) + T。
    // 其中 dist(i, X) 是原本路徑上 i 到 X 的距離。
    // 由於 X 在 i 到 1 的最短路徑上，dist(i, X) = dist[i] - dist[X]。
    // 所以新距離 = dist[i] - dist[X] + T。
    // 節省的時間 = dist[i] - (dist[i] - dist[X] + T) = dist[X] - T。
    // 前提是：
    // 1. X 在 i 的原最短路徑上。
    // 2. 新距離 < 原距離 => dist[X] - T > 0 => dist[X] > T。
    
    // 等等，題目說 "增加了一條從牛棚（田地 1）到他選擇的另一塊田地的捷徑"。
    // 農夫可以選擇任意一個點 X 來建造捷徑。我們要選一個 X 使得總節省時間最大。
    // 對於固定的 X，哪些牛會受益？
    // 只有那些原本路徑經過 X 的牛，且 dist[X] > T。
    // 每頭這樣的牛節省 (dist[X] - T)。
    // 總節省 = (dist[X] - T) * (所有路徑經過 X 的牛的數量)。
    
    // 問題轉化為：對於每個可能的 X (2..N)，計算有多少頭牛的 "字典序最小最短路徑" 經過 X。
    // 令 count[X] 為路徑經過 X 的牛的總數 (加權，權重為 C[i])。
    // 注意：如果牛就在 X (i=X)，也算經過 X。
    // 我們需要快速計算每個 X 的 count[X]。
    
    // 路徑結構是由 next_node 陣列定義的樹 (指向 1 的有向樹)。
    // 對於每個 i，路徑是 i -> next_node[i] -> next_node[next_node[i]] -> ... -> 1。
    // 這是一個以 1 為根的外向樹 (邊方向 i -> parent)。
    // X 在 i 的路徑上，等價於 i 在以 X 為根的子樹中 (如果把邊看作 X <- next_node[X] 這種反向關係？)
    // 不，邊是 i -> next_node[i]。所以 1 是匯点 (sink)。
    // 如果我們將邊反向：next_node[i] -> i，則形成一棵以 1 為根的樹，邊向外。
    // 在這種反向樹中，X 的子樹中的所有節點 i，其原路徑都會經過 X。
    // 所以 count[X] = sum(C[i]) for all i in subtree of X (in the reversed tree).
    
    // 算法：
    // 1. 建立反向樹：rev_adj[u] 包含所有 v 使得 next_node[v] == u。
    // 2. 從 1 開始 DFS/BFS 計算子樹和。
    
    vector<vector<int>> rev_tree(N + 1);
    for (int i = 2; i <= N; ++i) {
        int p = next_node[i];
        if (p != -1) {
            rev_tree[p].push_back(i);
        }
    }

    vector<long long> subtree_cows(N + 1, 0);
    // DFS 計算子樹和
    // 由於 N=10000，遞迴深度可能較大，但通常系統棧夠用。若擔心可用迭代。
    // 這裡用簡單的遞迴。
    
    // 為了避免遞迴過深導致 Stack Overflow (雖然 10000 通常沒事)，我们可以用拓撲排序順序或顯式棧。
    // 這裡用顯式棧進行後序遍歷。
    vector<int> order;
    queue<int> q_bfs;
    q_bfs.push(1);
    while(!q_bfs.empty()){
        int u = q_bfs.front(); q_bfs.pop();
        order.push_back(u);
        for(int v : rev_tree[u]){
            q_bfs.push(v);
        }
    }
    // 反向遍歷 order (從葉子到根)
    for (int i = N; i >= 0; --i) { // order 大小是 N
        int u = order[i];
        subtree_cows[u] += C[u];
        for (int v : rev_tree[u]) {
            subtree_cows[u] += subtree_cows[v];
        }
    }

    long long max_saving = 0;
    // 枚舉所有可能的 X (1..N)，但捷徑是連到 "另一塊田地"，所以 X != 1。
    // 題目說 "他選擇的另一塊田地"，暗示 X != 1。
    // 如果 X=1，捷徑長度 T，路徑 1->1 沒意義，節省 0。
    for (int x = 2; x <= N; ++x) {
        if (dist[x] > T) {
            long long saving = (long long)(dist[x] - T) * subtree_cows[x];
            if (saving > max_saving) {
                max_saving = saving;
            }
        }
    }

    cout << max_saving << endl;

    return 0;
}
