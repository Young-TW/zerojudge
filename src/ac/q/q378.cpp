#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    // 處理多筆測資直到 EOF
    while (cin >> N) {
        vector<int> a(N);
        vector<int> b(N);

        for (int i = 0; i < N; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < N; ++i) {
            cin >> b[i];
        }

        // dp[i][j] 表示考慮前 i 個出水口與前 j 個進水口時的最大水流量總和
        // 為了節省空間，我們可以使用滾動陣列或僅用兩行，但鑑於 N=2000, N*N*4bytes ≈ 16MB
        // 現代競賽環境通常允許 64MB~256MB，直接開二維陣列最安全且不易出錯
        // 若記憶體限制極嚴苛 (如 < 32MB)，則需改為一維 DP 優化
        // 此處使用 vector<vector<long long>> 以防總和超過 int 範圍 (雖然題目說輸出正整數，但累加可能很大)
        // 最大可能值：2000 * 10^6 = 2 * 10^9，剛好卡在 signed int 邊緣，建議用 long long
        
        // 使用一維 DP 優化空間複雜度至 O(N)
        // dp[j] 代表當前處理到第 i 個出水口時，匹配到第 j 個進水口的最大值
        // 我们需要保留上一行的 dp[j-1] 用於計算當前的 dp[j] (即 diagonal value)
        vector<long long> dp(N + 1, 0);

        for (int i = 1; i <= N; ++i) {
            long long prev_diag = 0; // 對應 dp[i-1][j-1]，初始時 j=0, dp[i-1][0]=0
            for (int j = 1; j <= N; ++j) {
                long long temp = dp[j]; // 儲存目前的 dp[j] 作為下一次迴圈的 prev_diag (即 dp[i-1][j])
                
                // 狀態轉移：
                // 1. 不選第 i 個出水口：dp[i-1][j] (即當前的 dp[j])
                // 2. 不選第 j 個進水口：dp[i][j-1] (即更新後的 dp[j-1])
                // 3. 連接 i 和 j：dp[i-1][j-1] + min(a[i-1], b[j-1]) (即 prev_diag + min...)
                
                long long connect_val = prev_diag + min(a[i-1], b[j-1]);
                
                // dp[j] = max(不選 i, 不選 j, 連接)
                // 注意：這裡的 dp[j] 在賦值前是 dp[i-1][j]
                // dp[j-1] 在本輪迴圈中已經更新為 dp[i][j-1]
                
                if (connect_val > dp[j]) {
                    dp[j] = connect_val;
                }
                if (dp[j-1] > dp[j]) {
                    dp[j] = dp[j-1];
                }
                
                prev_diag = temp; // 更新 prev_diag 為 dp[i-1][j] 供下一個 j 使用
            }
        }

        cout << dp[N] << "\n";
    }

    return 0;
}
