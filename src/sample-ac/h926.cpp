#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    while (cin >> n >> k) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // pre[i] = 最大的 j 使得 [j, i] 是合法的（無重複）
        // 也就是說，對於每個 i，我們要找最左邊的起點，使得從該起點到 i 沒有重複元素
        vector<int> pre(n + 1, 0);
        vector<int> last_pos(100001, -1); // 美食編號最大為 10^5
        int left = 0;
        
        for (int i = 0; i < n; ++i) {
            if (last_pos[a[i]] >= left) {
                left = last_pos[a[i]] + 1;
            }
            last_pos[a[i]] = i;
            pre[i + 1] = left; // pre[i+1] 對應到以 i 結尾的最左合法起點
        }

        // dp[t][i] = 用 t 個人覆蓋前 i 個攤位能得到的最大數量
        // 但這樣會 O(k*n)，需要優化
        
        // 我們使用貪心 + 雙端隊列優化的 DP
        // dp[i] = 考慮前 i 個攤位，使用若干個人的最大覆蓋數
        // 但我們需要精確控制人數為 k
        
        // 令 dp[t][i] 表示用 t 個人處理前 i 個攤位的最大答案
        // 轉移：dp[t][i] = max(dp[t][i-1], dp[t-1][j] + (i-j)) for all j where pre[i] <= j < i
        // 這可以重寫為：dp[t][i] = max(dp[t][i-1], max_{j in [pre[i], i-1]} (dp[t-1][j] - j) + i)
        
        // 由於 k 可能很大，我們不能用二維 DP
        // 但注意到我們只需要最後一層和前一個人的結果
        
        // 使用滾動陣列 + deque 優化
        vector<int> dp_prev(n + 1, 0);
        vector<int> dp_curr(n + 1, 0);
        
        // 初始化：0 個人時，答案都是 0
        for (int i = 0; i <= n; ++i) {
            dp_prev[i] = 0;
        }
        
        for (int t = 1; t <= k; ++t) {
            // 對於第 t 個人，我們計算 dp_curr
            // dp_curr[i] = max(dp_curr[i-1], max_{j in [pre[i], i-1]} (dp_prev[j] - j) + i)
            
            deque<pair<int, int>> dq; // 存儲 {value, index}，value = dp_prev[j] - j
            // 維護單調遞減隊列
            
            dp_curr[0] = 0;
            
            for (int i = 1; i <= n; ++i) {
                // 加入新的候选 j = i-1
                int val = dp_prev[i - 1] - (i - 1);
                while (!dq.empty() && dq.back().first <= val) {
                    dq.pop_back();
                }
                dq.push_back({val, i - 1});
                
                // 移除不在範圍內的候選 (j < pre[i])
                while (!dq.empty() && dq.front().second < pre[i]) {
                    dq.pop_front();
                }
                
                // 計算 dp_curr[i]
                int best = dq.front().first + i;
                dp_curr[i] = max(dp_curr[i - 1], best);
            }
            
            // 交換 dp_prev 和 dp_curr
            swap(dp_prev, dp_curr);
        }
        
        cout << dp_prev[n] << "\n";
    }

    return 0;
}
