#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    if (!(cin >> N >> K)) return 0;

    // ladder_start[i] 儲存格子 i 作為梯子起點時，對應的終點。
    // 若 i 不是梯子起點，則為 0。
    // 題目保證每一格最多只有一個梯子起點。
    vector<int> ladder_start(N + 1, 0);

    for (int k = 0; k < K; ++k) {
        int u, v;
        cin >> u >> v;
        // u 是起點，v 是終點
        if (u <= N) {
            ladder_start[u] = v;
        }
    }

    const int MOD = 998244353;

    // dp[i] 表示到達格子 i 的方法數
    // 使用 long long 防止加法溢出後再取模
    vector<long long> dp(N + 1, 0);

    // 初始狀態：在第 1 格，方法數為 1
    dp[1] = 1;

    // 從第 1 格推到第 N-1 格 (因為到了 N 就結束了，不需要從 N 再往外推)
    // 實際上只要 i < N，因為從 i 可以擲骰子到達更遠的地方
    for (int i = 1; i < N; ++i) {
        if (dp[i] == 0) continue; // 如果無法到達此格，則無需處理

        // 枚舉骰子點數 1 ~ 6
        for (int x = 1; x <= 6; ++x) {
            int next_pos = i + x;
            
            // 題目規則：移動到 min(i+x, N)
            if (next_pos >= N) {
                // 如果超過或等於 N，則直接到達終點 N
                // 注意：題目說終點是 N，且梯子起點 i < j <= N，但通常終點不會設為梯子起點
                // 即使 N 是梯子起點 (雖然題目邏輯上不太可能，因為遊戲結束)，我們也先到達 N
                // 根據題目 "遊戲將持續直到玩家到達最後一格 N 就視為遊戲結束"
                // 所以一旦下一步 >= N，就是到達 N。
                
                dp[N] = (dp[N] + dp[i]) % MOD;
            } else {
                // 如果 next_pos < N，檢查是否有梯子
                if (ladder_start[next_pos] != 0) {
                    // 有梯子，直接跳到梯子終點
                    int dest = ladder_start[next_pos];
                    // 題目保證梯子終點 j <= N
                    if (dest > N) dest = N; // 防禦性編程，雖題目說 j <= N
                    
                    // 注意：題目說 "每次移動只會爬一次梯子"
                    // 這裡我們是直接推送到 dest，符合規則
                    dp[dest] = (dp[dest] + dp[i]) % MOD;
                } else {
                    // 沒有梯子，正常移動到 next_pos
                    dp[next_pos] = (dp[next_pos] + dp[i]) % MOD;
                }
            }
        }
    }

    cout << dp[N] << endl;

    return 0;
}
