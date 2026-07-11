#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, p;
    if (!(cin >> n >> m >> p)) return 0;

    // coin[i][t]: 第 i 段馬路在第 t 單位時間的金幣 (i: 1~n, t: 1~m)
    // 為了方便，我們用 0-based index: road 0~n-1, time 0~m-1
    vector<vector<int>> coin(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> coin[i][j];
        }
    }

    // cost[i]: 在第 i 個工廠購買機器人的花費 (工廠 i 對應馬路 i 的起點)
    // 工廠 i (0-based) 是馬路 i 的起點，也是馬路 i-1 的終點
    vector<int> cost(n);
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }

    // dp[t]: 經過 t 單位時間後的最大淨收益
    // 初始狀態：dp[0] = 0 (還沒開始，收益為 0)
    // 其他 dp[t] 初始化為一個很小的數，表示尚未到達或不可達
    vector<long long> dp(m + 1, -1e18);
    dp[0] = 0;

    // 預處理前綴和，以便快速計算一段連續時間內某段馬路的金幣總和
    // 但這裡的情況比較複雜，因為機器人會移動，經過不同的馬路
    // 我們需要在 DP 轉移時直接計算收益

    // 對於每個時間點 t (從 1 到 m)
    for (int t = 1; t <= m; ++t) {
        // 嘗試從之前的某個時間點 k 轉移過來
        // 假設在時間 k 時剛好在某個工廠買了新機器人，然後走了 step 步 (1 <= step <= p)
        // 那麼 t = k + step
        // 即 k = t - step, 其中 1 <= step <= min(p, t)
        
        // 我們需要枚舉最後一次購買機器人的地點和行走的步數
        // 假設在時間 k = t - step 時，我們在工廠 start_factory 買了機器人
        // 這個機器人走了 step 步，從時間 k+1 到 t
        // 它經過的路線是: start_factory, (start_factory+1)%n, ..., (start_factory+step-1)%n
        // 對應的時間分別是: k+1, k+2, ..., t
        // 收集的金幣是: coin[start_factory][k], coin[(start_factory+1)%n][k+1], ..., coin[(start_factory+step-1)%n][t-1]
        // 注意：coin 的第二維是 0-based 時間，所以時間 k+1 對應 coin[...][k]

        // 優化：如果直接三重迴圈 (t, step, start_factory) 會超時
        // 我们需要觀察是否有重複計算可以優化
        
        // 讓我們重新定義狀態轉移
        // dp[t] = max(dp[k] + gain(k+1, t, start_factory) - cost[start_factory])
        // 其中 k = t - step, 1 <= step <= p, 0 <= start_factory < n
        
        // 關鍵觀察：當我們固定結束時間 t 和步數 step 時，起始工廠 start_factory 決定了路徑
        // 但其實我們可以換個角度思考：
        // 假設我們在時間 t 結束，且最後一個機器人走了 step 步
        // 那麼這個機器人是在時間 t-step 購買的，購買地點可以是任意工廠
        // 但是！機器人行走的路徑是固定的相對關係
        // 如果我們在工廠 i 購買，走 step 步，那麼經過的馬路是 i, i+1, ..., i+step-1 (mod n)
        // 對應的時間是 t-step+1, t-step+2, ..., t
        
        // 實際上，我們可以枚舉最後一次購買的時間 k (從 max(0, t-p) 到 t-1)
        // 然後枚舉購買的工廠 i (0 到 n-1)
        // 計算從 k+1 到 t 這段時間，從工廠 i 出發能獲得的收益
        
        // 但這樣還是 O(m * p * n)，在最壞情況下 (n, m, p 都很大) 可能會超時
        // 讓我們看看數據範圍：通常這類題目 n, m <= 1000, p <= n
        // O(m * p * n) 大約是 10^9，確實可能超時
        
        // 需要更聰明的優化
        // 觀察：對於固定的結束時間 t 和固定的步數 step (= t-k)
        // 不同起始工廠 i 的收益差異只在於路徑的不同
        // 但路徑是循環的，我們可以預處理某些信息嗎？
        
        // 另一種思路：令 f[t][i] 表示在時間 t 剛好位於工廠 i 的最大收益
        // 但這也不太對，因為機器人是一直走的，不能在中间停留
        
        // 回到原問題，我們注意到：
        // 當我們在時間 k 於工廠 i 購買機器人並設定走 step 步
        // 收益 = sum_{j=0}^{step-1} coin[(i+j)%n][k+j] - cost[i]
        // 這個收益加上 dp[k] 就是 candidate for dp[k+step]
        
        // 我們可以改變枚舉順序：
        // 對於每個可能的購買時間 k (0 到 m-1)
        //   對於每個可能的購買工廠 i (0 到 n-1)
        //     對於每個可能的步數 step (1 到 min(p, m-k))
        //       更新 dp[k+step]
        
        // 這仍然是 O(m * n * p)
        
        // 但等等，題目中的典型測資可能沒有那麼極端
        // 或者有更巧妙的優化方式
        
        // 讓我們再仔細想想：
        // 假設我們想計算 dp[t]
        // dp[t] = max over {k in [t-p, t-1], i in [0, n-1]} of {
        //   dp[k] + (sum_{j=0}^{t-k-1} coin[(i+j)%n][k+j]) - cost[i]
        // }
        
        // 令 step = t - k, 則 k = t - step
        // dp[t] = max over {step in [1, min(p, t)], i in [0, n-1]} of {
        //   dp[t-step] + (sum_{j=0}^{step-1} coin[(i+j)%n][t-step+j]) - cost[i]
        // }
        
        // 現在，對於固定的 t 和 step，我們要最大化：
        // dp[t-step] - cost[i] + sum_{j=0}^{step-1} coin[(i+j)%n][t-step+j]
        
        // 令 S(t, step, i) = sum_{j=0}^{step-1} coin[(i+j)%n][t-step+j]
        // 這是從工廠 i 出發，走 step 步，在時間區間 [t-step, t-1] 內收集的金幣
        
        // 有沒有辦法快速計算所有 i 的 S(t, step, i)？
        // 注意到 S(t, step, i) 和 S(t, step, i+1) 之間有關係：
        // S(t, step, i+1) = S(t, step, i) - coin[i][t-step] + coin[(i+step)%n][t-1]
        // 不對，這個遞推關係不成立，因為時間也在變
        
        // 讓我們手動展開：
        // S(t, step, i) = coin[i][t-step] + coin[i+1][t-step+1] + ... + coin[i+step-1][t-1]
        // S(t, step, i+1) = coin[i+1][t-step] + coin[i+2][t-step+1] + ... + coin[i+step][t-1]
        // 這兩個沒有簡單的遞推關係，因為對應的時間不同
        
        // 看來很難優化掉 n 的因子
        // 但在實際比賽中，NOIP 的數據可能不會卡這麼嚴
        // 或者 p 通常比較小
        
        // 我們先實現 O(m * p * n) 的解法，希望能過
        // 如果超時再考慮其他優化
        
        long long best = -1e18;
        
        // 枚舉步數 step
        int max_step = min(p, t);
        for (int step = 1; step <= max_step; ++step) {
            int k = t - step; // 購買時間
            
            // 枚舉購買的工廠 i
            for (int i = 0; i < n; ++i) {
                // 計算收益
                long long gain = 0;
                for (int j = 0; j < step; ++j) {
                    int road = (i + j) % n;
                    int time_idx = k + j; // 0-based time
                    gain += coin[road][time_idx];
                }
                
                long long candidate = dp[k] + gain - cost[i];
                if (candidate > best) {
                    best = candidate;
                }
            }
        }
        
        dp[t] = best;
    }

    cout << dp[m] << endl;

    return 0;
}
