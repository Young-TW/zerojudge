#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1005;
const int MAXM = 1005;

int N, M;
int parent_node[MAXN];
int c[MAXN], d[MAXN];
vector<int> children[MAXN];
int dp[MAXN][MAXM];
int subtree_sum[MAXN];
int subtree_cnt[MAXN];

void dfs(int u) {
    subtree_sum[u] = c[u];
    subtree_cnt[u] = 1;
    
    for (int v : children[u]) {
        dfs(v);
        subtree_sum[u] += subtree_sum[v];
        subtree_cnt[u] += subtree_cnt[v];
    }
}

void solve_knapsack(int u) {
    // 初始化當前節點的 DP 表
    // 選項 1: 不買任何以 u 為根的子樹商品
    for (int j = 0; j <= M; ++j) {
        dp[u][j] = 0;
    }

    // 選項 2: 單獨購買 u (花費 c[u], 價值 c[u])
    // 這需要結合子樹的背包結果，但這裡我們先處理子樹合併，再考慮單獨買 u 或整包買
    // 標準樹形背包做法：先合併所有子節點
    
    // 臨時數組用於合併子節點
    static int temp_dp[MAXM];
    memset(temp_dp, 0, sizeof(temp_dp));
    
    // 合併子節點
    for (int v : children[u]) {
        solve_knapsack(v);
        // 將子節點 v 的背包合併到 temp_dp
        for (int j = M; j >= 0; --j) {
            for (int k = 0; k <= j; ++k) {
                if (temp_dp[j - k] + dp[v][k] > temp_dp[j]) {
                    temp_dp[j] = temp_dp[j - k] + dp[v][k];
                }
            }
        }
    }
    
    // 現在 temp_dp[j] 表示在 u 的子節點中花費 j 能獲得的最大價值
    // 接下來考慮 u 本身
    
    // 情況 A: 不買 u，也不買整棵子樹，只買子節點中的部分
    for (int j = 0; j <= M; ++j) {
        dp[u][j] = temp_dp[j];
    }
    
    // 情況 B: 單獨買 u (花費 c[u])，然後可以搭配子節點中的選擇
    // 注意：如果單獨買 u，就不能用 d[u] 買整棵子樹，但可以自由選擇子節點
    if (c[u] <= M) {
        for (int j = M; j >= c[u]; --j) {
            int val = c[u] + temp_dp[j - c[u]];
            if (val > dp[u][j]) {
                dp[u][j] = val;
            }
        }
    }
    
    // 情況 C: 用 d[u] 買整棵子樹 (花費 d[u], 價值 subtree_sum[u])
    if (d[u] <= M) {
        int val = subtree_sum[u];
        if (val > dp[u][d[u]]) {
            dp[u][d[u]] = val;
        }
        // 更新大於 d[u] 的情況
        for (int j = d[u] + 1; j <= M; ++j) {
            if (val > dp[u][j]) {
                dp[u][j] = val;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> N >> M) {
        for (int i = 0; i < N; ++i) {
            children[i].clear();
        }
        
        vector<int> roots;
        for (int i = 0; i < N; ++i) {
            cin >> parent_node[i];
            if (parent_node[i] == -1) {
                roots.push_back(i);
            } else {
                children[parent_node[i]].push_back(i);
            }
        }
        
        for (int i = 0; i < N; ++i) {
            cin >> c[i] >> d[i];
        }
        
        // 計算每棵子樹的總價值
        for (int root : roots) {
            dfs(root);
        }
        
        // 初始化全局 DP
        static int global_dp[MAXM];
        memset(global_dp, 0, sizeof(global_dp));
        
        // 對每個根節點進行樹形 DP
        for (int root : roots) {
            solve_knapsack(root);
            // 將當前根的結果合併到全局 DP
            for (int j = M; j >= 0; --j) {
                for (int k = 0; k <= j; ++k) {
                    if (global_dp[j - k] + dp[root][k] > global_dp[j]) {
                        global_dp[j] = global_dp[j - k] + dp[root][k];
                    }
                }
            }
        }
        
        cout << global_dp[M] << "\n";
    }
    
    return 0;
}
