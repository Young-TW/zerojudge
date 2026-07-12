#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
vector<int> adj[260];
bool visited[260];
bool in_set[260];
int max_coins;

// 檢查當前選擇的集合是否合法（沒有相鄰的房間同時被選）
bool is_valid() {
    for (int i = 1; i <= N; ++i) {
        if (in_set[i]) {
            for (size_t j = 0; j < adj[i].size(); ++j) {
                int neighbor = adj[i][j];
                if (in_set[neighbor]) {
                    return false;
                }
            }
        }
    }
    return true;
}

// 回溯法尋找最大獨立集
void backtrack(int room, int current_count) {
    // 剪枝：如果剩下的房間全選也不可能超過目前的最大值，則返回
    if (current_count + (N - room + 1) <= max_coins) {
        return;
    }

    if (room > N) {
        if (is_valid()) {
            if (current_count > max_coins) {
                max_coins = current_count;
            }
        }
        return;
    }

    // 嘗試選擇當前房間
    in_set[room] = true;
    // 提前檢查合法性以進行剪枝
    bool possible = true;
    for (size_t i = 0; i < adj[room].size(); ++i) {
        if (in_set[adj[room][i]]) {
            possible = false;
            break;
        }
    }
    
    if (possible) {
        backtrack(room + 1, current_count + 1);
    }

    // 嘗試不選擇當前房間
    in_set[room] = false;
    backtrack(room + 1, current_count);
}

int main() {
    while (cin >> N) {
        // 初始化
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
            visited[i] = false;
            in_set[i] = false;
        }
        max_coins = 0;

        int u, v;
        while (cin >> u && u != 0) {
            cin >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        backtrack(1, 0);

        cout << max_coins << endl;
        // 根據題目範例輸出的額外說明文字
        // 這裡需要重構一次來找出具體是哪幾個房間，但題目通常只要求數值
        // 然而範例輸出有第二行 "可以拿2 3 4的錢幣"
        // 為了完全符合範例輸出，我們需要再跑一次找出解路徑
        // 由於 N <= 255 且時間限制通常寬鬆，我們可以簡單地再跑一次帶記錄的版本
        // 或者在上面的 backtrack 中記錄最佳解。
        // 為了簡化邏輯並確保通過，我們在找到新的 max_coins 時記錄狀態。
        
        // 重新實作帶有記錄功能的回溯
        vector<int> best_solution;
        vector<int> current_solution;
        
        // 重置狀態變數以便第二次執行或修改邏輯
        // 實際上我們可以將上述邏輯合併，但為了清晰，這裡展示如何獲取解路徑
        // 由於上面已經算出 max_coins，我們可以用另一個函數找出一組解即可
        
        auto find_solution = [&](auto&& self, int r, int cnt) -> void {
            if (r > N) {
                if (cnt == max_coins) {
                    // 驗證並保存
                    bool ok = true;
                    for(int i=1; i<=N; ++i) {
                        if (in_set[i]) {
                            for(int nb : adj[i]) {
                                if(in_set[nb]) { ok = false; break; }
                            }
                        }
                        if(!ok) break;
                    }
                    if(ok) {
                        best_solution.clear();
                        for(int i=1; i<=N; ++i) if(in_set[i]) best_solution.push_back(i);
                    }
                }
                return;
            }
            if (best_solution.size() > 0) return; // 找到一組就停

            // 選
            in_set[r] = true;
            bool possible = true;
            for(int nb : adj[r]) if(in_set[nb]) possible = false;
            if(possible) self(self, r+1, cnt+1);
            
            if(best_solution.size() > 0) return;

            // 不選
            in_set[r] = false;
            self(self, r+1, cnt);
        };
        
        // 清空並重跑以找出路徑
        memset(in_set, 0, sizeof(in_set));
        find_solution(find_solution, 1, 0);

        cout << "可以拿";
        for (size_t i = 0; i < best_solution.size(); ++i) {
            cout << best_solution[i];
            if (i != best_solution.size() - 1) cout << " ";
        }
        cout << "的錢幣" << endl;
    }
    return 0;
}
