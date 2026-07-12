#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 305;
const int INF = 1e9;

vector<int> adj[MAXN];
vector<int> levels[MAXN];
int parent_node[MAXN];
bool cut[MAXN]; // cut[u] = true 表示切斷 parent[u] -> u 的邊
int n, p;
int min_infected;

// DFS 建立樹結構與分層
void dfs_build(int u, int p_node, int depth) {
    parent_node[u] = p_node;
    levels[depth].push_back(u);
    for (size_t i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (v != p_node) {
            dfs_build(v, u, depth + 1);
        }
    }
}

// 計算當前 cut 狀態下被感染的人數
// 規則：若節點 u 的父節點到 u 的邊被切斷，則 u 及其子孫都不會感染
// 否則若父節點被感染，則 u 也被感染
int count_infected() {
    int count = 0;
    // 根節點 1 一定被感染（除非我們能切斷它？但題目說節點 1 已感染，且只能切邊）
    // 所以節點 1 永遠算感染
    vector<bool> infected(n + 1, false);
    infected[1] = true;
    count = 1;

    // 按層級順序處理（BFS 順序）
    for (int d = 1; ; ++d) {
        if (levels[d].empty()) break;
        for (size_t i = 0; i < levels[d].size(); ++i) {
            int u = levels[d][i];
            int par = parent_node[u];
            // 如果父節點沒被感染，或邊被切斷，則 u 不會感染
            if (!infected[par] || cut[u]) {
                infected[u] = false;
            } else {
                infected[u] = true;
                count++;
            }
        }
    }
    return count;
}

// 回溯搜尋：每一層選擇切斷哪一條邊（從該層的節點中選一個切斷其與父節點的邊）
// level_idx: 目前處理的層級索引（從 1 開始，因為第 0 層只有根節點）
void backtrack(int level_idx) {
    // 檢查是否還有下一層
    if (levels[level_idx].empty()) {
        // 沒有更多層可以切，計算當前感染人數
        int infected_count = count_infected();
        if (infected_count < min_infected) {
            min_infected = infected_count;
        }
        return;
    }

    // 剪枝：即使後面都不切，當前最小可能值是多少？
    // 這裡先不做複雜剪枝，直接枚舉

    // 選項 1：在這一層不切任何邊（允許整層都感染）
    // 注意：題目說每個週期「只能」切一條邊，但不是「必須」切一條邊嗎？
    // 重讀題目："在一个疾病传播周期内，只能设法切断一条传播途径"
    // 這表示可以選擇切或不切？還是必須切一條？
    // 實際上，如果不切會導致更多人感染，所以最優解通常會切。
    // 但為了嚴謹，我們考慮兩種情況：切其中一個，或者完全不切（如果該層存在）
    // 然而，仔細想：如果不切，那下一輪還是會繼續傳播。題目說「當不可能有健康人被感染時，疾病就中止傳播」
    // 所以我們必須在每一層（只要該層有可切的邊）選擇切一條邊來最小化總感染數。
    // 但其實也可以選擇不切，讓整層感染，然後在下一層再切。
    // 因此，對於每一層，我們可以選擇：
    //   - 切斷該層某個節點與其父節點的邊（共 k 種選擇，k = 該層節點數）
    //   - 或者不切任何邊（1 種選擇）
    // 總共 k+1 種選擇。

    // 但注意：如果不切任何邊，那麼該層所有節點都會被感染（假設父層有感染），然後進入下一層。
    // 我們需要嘗試所有可能性。

    // 先嘗試不切任何邊的情況
    // （實際上，不切等於切一個虛擬的「無操作」，我們直接遞迴到下一層）
    // 但要注意：如果不切，那麼該層所有節點都可能被感染（取決於父節點），然後繼續往下。
    // 我們直接遞迴：
    
    // 選項 A：不切任何邊
    backtrack(level_idx + 1);

    // 選項 B：切斷該層某一個節點 u 的邊（cut[u] = true）
    for (size_t i = 0; i < levels[level_idx].size(); ++i) {
        int u = levels[level_idx][i];
        cut[u] = true;
        backtrack(level_idx + 1);
        cut[u] = false; // 回溯
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n >> p) {
        // 初始化
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
            levels[i].clear();
            cut[i] = false;
            parent_node[i] = 0;
        }
        levels[0].clear();

        for (int i = 0; i < p; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // 建立樹結構（以 1 為根）
        dfs_build(1, 0, 0);

        min_infected = INF;

        // 從第 1 層開始回溯（第 0 層是根，無法切）
        backtrack(1);

        cout << min_infected << "\n";
    }

    return 0;
}
