#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 2-SAT 問題求解器
// 變數 x_i 表示是否選擇玩具 i
// 每個孩子有兩個願望 (a, b)，條件為 (x_a OR x_b) = true
// 我們要最小化選擇的玩具數量，這在一般的 2-SAT 中不是直接支持的。
// 但注意到題目約束：n <= 100 或 m <= 400。
// 當 n 很小時，我們可以枚舉所有可能的玩具組合？不行，2^100 太大。
// 當 m 很小時，也許可以用其他方法？
// 重新審視問題：這是一個「最小滿足 2-SAT」問題，通常是 NP-hard。
// 但題目給的特殊約束 n <= 100 或 m <= 400 暗示了某種特殊解法。
// 實際上，這個問題可以轉化為圖論中的「頂點覆蓋」或相關問題的變體嗎？
// 不，讓我們再仔細看約束。n 是不同玩具的數量，最多 250，但每筆測資保證 n<=100 或 m<=400。
// 如果 n <= 100，我們可以嘗試用分支限界或狀態壓縮 DP 嗎？2^100 還是不行。
// 等等，這個問題其實是「Hitting Set」問題的變體，或者是「Set Cover」的對偶？
// 每個孩子是一個集合 {a, b}，我們要選最少的元素使得每個集合至少有一個元素被選中。
// 這正是「Vertex Cover」在一般圖上的推廣？不，這是「Hitting Set」問題，其中每個集合大小為 2。
// 當每個集合大小為 2 時，這個問題等價於在圖上找最小頂點覆蓋！
// 建構一個圖，節點是玩具，每個孩子 (a, b) 對應一條邊 (a, b)。
// 我們需要選擇最少的節點，使得每條邊至少有一個端點被選中。這就是最小頂點覆蓋問題。
// 最小頂點覆蓋在一般圖上是 NP-hard，但在二分圖上可以在多項式時間內解決（通過最大匹配）。
// 然而，這裡的圖不一定是二分圖。
// 但題目給了特殊約束：n <= 100 或 m <= 400。
// 如果 m <= 400（邊數少），我們可以用指數時間複雜度關於 m 的算法嗎？或者關於頂點覆蓋大小的算法？
// 如果 n <= 100（節點數少），我們可以用指數時間複雜度關於 n 的算法嗎？
// 對於最小頂點覆蓋，有一個簡單的 DFS + 剪枝算法，時間複雜度 O(2^k * n)，其中 k 是最小頂點覆蓋的大小。
// 或者用 branching algorithm: O(1.618^k) 或 O(2^n)。
// 由於 n <= 100，O(2^n) 還是不行。但如果最小頂點覆蓋很小呢？
// 另一種思路：因為 m <= 400 或 n <= 100，我們可以嘗試用 meet-in-the-middle 或其他技巧？
// 其實，對於最小頂點覆蓋，當 n <= 100 時，我們可以使用基於递归回溯的算法，加上強力的剪枝。
// 或者，注意到如果圖是稀疏的（m 小），可能有更好的方法。
// 但最直接的解法是：使用 branching algorithm for Vertex Cover。
// 算法：
// 1. 如果沒有邊了，返回 0。
// 2. 任選一條邊 (u, v)。
// 3. 要麼選 u，要麼選 v（或兩者都選，但最小化解不會同時選除非必要，branching 時考慮選 u 或選 v 即可）。
// 4. 遞迴：min(1 + VC(G - {u}), 1 + VC(G - {v}))。
// 為了優化，我們可以：
// - 移除孤立點。
// - 如果某個點的度數為 1，我們可以貪心地選它的鄰居？不，這不一定正確。但有一些規則可以簡化。
// - 使用 memoization？狀態太多。
// - 剪枝：如果當前已選數量 >= 目前最佳解，則剪枝。
// 由於 n <= 100 或 m <= 400，這個 branching algorithm 應該能過。最壞情況是 O(2^min(n, m))，但實際會快很多。
// 另外，當 m <= 400 時，邊數不多，branching 深度不會太深。
// 當 n <= 100 時，節點數不多，也可以接受。
// 我們來實現這個 branching algorithm。

struct Edge {
    int u, v;
};

int best_ans;
vector<Edge> edges;
bool removed[255]; // 標記節點是否被移除（即被選入頂點覆蓋）
vector<int> adj[255]; // 鄰接表，用於快速找到與某節點相關的邊

// 計算當前圖中的邊數（未被覆蓋的邊）
int count_remaining_edges() {
    int cnt = 0;
    for (const auto& e : edges) {
        if (!removed[e.u] && !removed[e.v]) {
            cnt++;
        }
    }
    return cnt;
}

// 找出第一條未被覆蓋的邊
bool find_first_edge(int& u, int& v) {
    for (const auto& e : edges) {
        if (!removed[e.u] && !removed[e.v]) {
            u = e.u;
            v = e.v;
            return true;
        }
    }
    return false;
}

void dfs(int current_count) {
    // 剪枝：如果當前數量已經不小於最佳解，返回
    if (current_count >= best_ans) {
        return;
    }
    
    int u, v;
    if (!find_first_edge(u, v)) {
        // 沒有邊了，更新最佳解
        best_ans = current_count;
        return;
    }
    
    // Branch 1: 選擇 u
    removed[u] = true;
    dfs(current_count + 1);
    removed[u] = false;
    
    // Branch 2: 選擇 v
    removed[v] = true;
    dfs(current_count + 1);
    removed[v] = false;
}

int solve() {
    int m;
    while (cin >> m && m != 0) {
        vector<pair<int, int>> wishes(m);
        vector<int> toys;
        for (int i = 0; i < m; ++i) {
            cin >> wishes[i].first >> wishes[i].second;
            toys.push_back(wishes[i].first);
            toys.push_back(wishes[i].second);
        }
        
        // 離散化玩具編號
        sort(toys.begin(), toys.end());
        toys.erase(unique(toys.begin(), toys.end()), toys.end());
        
        int n = toys.size();
        // 映射原始玩具編號到 0..n-1
        auto get_id = [&](int toy) -> int {
            return lower_bound(toys.begin(), toys.end(), toy) - toys.begin();
        };
        
        edges.clear();
        for (int i = 0; i < m; ++i) {
            int u = get_id(wishes[i].first);
            int v = get_id(wishes[i].second);
            if (u == v) {
                // 如果孩子兩個願望相同，則必須選這個玩具
                // 我們可以預先處理這種情況，但為了簡單，直接加邊，算法會自動處理
                edges.push_back({u, v});
            } else {
                edges.push_back({u, v});
            }
        }
        
        // 初始化
        memset(removed, 0, sizeof(bool) * n);
        best_ans = n; // 最壞情況：選所有玩具
        
        // 開始 DFS
        dfs(0);
        
        cout << best_ans << endl;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
