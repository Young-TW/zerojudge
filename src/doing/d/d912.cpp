#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 10005;
int N;
int D[MAXN];
int match_left[MAXN]; // match_left[i] = T_i (左側 i 匹配到的右側節點)
int match_right[MAXN]; // match_right[j] = i (右側 j 被左側哪個 i 匹配)
bool vis[MAXN];
vector<int> adj[MAXN]; // adj[i] 儲存 i 可以轉換成的兩個可能值，已排序

bool dfs(int u) {
    for (size_t i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (vis[v]) continue;
        vis[v] = true;
        
        if (match_right[v] == -1 || dfs(match_right[v])) {
            match_left[u] = v;
            match_right[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;

    for (int i = 0; i < N; ++i) {
        cin >> D[i];
    }

    // 構建二分圖
    // 左側節點: 0 ~ N-1 (代表原序列的索引 i)
    // 右側節點: 0 ~ N-1 (代表變換後的值 T_i)
    // 對於每個 i，根據 D[i] 計算可能的 T_i
    // D(i, T_i) = min(|i - T_i|, N - |i - T_i|) = d
    // 這意味著 |i - T_i| = d 或 |i - T_i| = N - d
    // 所以 T_i 可能是 (i + d) % N, (i - d + N) % N, (i + (N-d)) % N, (i - (N-d) + N) % N
    // 實際上只有兩個不同的值，因為 (i+d)%N 和 (i-(N-d)+N)%N 是一樣的
    
    for (int i = 0; i < N; ++i) {
        int d = D[i];
        int cand1 = (i + d) % N;
        int cand2 = (i - d + N) % N;
        
        adj[i].clear();
        adj[i].push_back(cand1);
        if (cand1 != cand2) {
            adj[i].push_back(cand2);
        }
        
        // 為了字典序最小，我們希望前面的 i 盡可能選到小的值。
        // 但匈牙利算法是從左到右匹配，如果在 DFS 中按照鄰接表順序嘗試，
        // 並且在發現衝突時能夠重新調整之前的匹配，那麼我們需要確保鄰接表是有序的。
        // 這裡我們將候補值排序，這樣在 DFS 時會優先嘗試較小的值。
        sort(adj[i].begin(), adj[i].end());
    }

    // 初始化匹配陣列
    memset(match_left, -1, sizeof(match_left));
    memset(match_right, -1, sizeof(match_right));

    // 為了得到字典序最小的解，我們需要從左到右依次為每個 i 尋找匹配。
    // 標準的匈牙利算法如果直接跑，可能無法保證字典序最小，因為後面的匹配可能會影響前面。
    // 正確的做法是：對於每個 i (從 0 到 N-1)，嘗試為它尋找一個匹配。
    // 在尋找過程中，如果發生衝突，則嘗試調整之前的匹配。
    // 由於我們在構建鄰接表時已經將候補值从小到大排序，
    // 並且在 DFS 中按順序嘗試，這樣就能保證在可行情況下選擇最小的值。
    
    bool possible = true;
    for (int i = 0; i < N; ++i) {
        memset(vis, 0, sizeof(vis));
        if (!dfs(i)) {
            possible = false;
            break;
        }
    }

    if (!possible) {
        cout << "No Answer" << endl;
    } else {
        for (int i = 0; i < N; ++i) {
            if (i > 0) cout << " ";
            cout << match_left[i];
        }
        cout << endl;
    }

    return 0;
}
