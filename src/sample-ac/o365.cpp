#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int N, M;
        long long C;
        cin >> N >> M >> C;

        vector<long long> w(N);
        for (int i = 0; i < N; ++i) {
            cin >> w[i];
        }

        vector<long long> a(M);
        for (int i = 0; i < M; ++i) {
            cin >> a[i];
        }

        // 計算單個工期內，在「不能連續兩天工作」限制下，最多能選幾天的工資總和（權重為 1）
        // 以及選中的天數對應的原始工資總和。
        // 但這裡每個員工的 w_i 不同，所以不能預先算好。
        // 對於每個員工，我們需要找到一個子集 S ⊆ {0, ..., M-1}，使得 S 中沒有兩個相鄰的元素，
        // 並且 sum_{j in S} (a[j] + k * w[i]) >= C，求最小的 k。
        // sum_{j in S} (a[j] + k * w[i]) = sum_{j in S} a[j] + k * w[i] * |S|
        // 令 base_sum(S) = sum_{j in S} a[j], count(S) = |S|
        // 則總收入 = base_sum(S) + k * w[i] * count(S)
        // 我們希望對於固定的 k，最大化這個值。
        // 但 k 是我們要二分搜尋的變數。
        // 觀察：對於固定的員工 i，其學習力 w = w[i] 是定值。
        // 總收入 = base_sum(S) + k * w * count(S) = sum_{j in S} (a[j] + k * w)
        // 這等價於：在第 k 個工期（實際是第 k+1 次工作，因為 k=0 是第一個工期），
        // 每天的工資變成 a[j] + k * w。
        // 我們要在這 M 天中，選出不相鄰的天數，使得總工資最大。
        // 然後檢查這個最大值是否 >= C。
        
        // 因此，對於每個員工，我們可以二分搜尋最小的 k (工期數，從 1 開始計數，但公式中用 k-1)
        // 設 x = 工期數 (x >= 1)，則該員工在第 x 個工期的每日工資為 a[j] + (x-1)*w
        // 我們需要 max_{S} sum_{j in S} (a[j] + (x-1)*w) >= C
        // 即 max_{S} [ sum_{j in S} a[j] + (x-1)*w * |S| ] >= C
        
        // 注意：max_{S} [ sum_{j in S} a[j] + K * |S| ] 不等於 max_{S} sum_{j in S} a[j] + K * max_{S}|S|
        // 因為使 base_sum 最大的 S 和使 |S| 最大的 S 可能不同。
        // 但是，對於固定的 K = (x-1)*w，我們可以重新定義每一天的價值為 v[j] = a[j] + K
        // 然後問題變成：在 v[0..M-1] 中選不相鄰元素使總和最大。這是一個經典 DP。
        // dp[i] = 前 i 天能獲得的最大收益
        // dp[i] = max(dp[i-1], dp[i-2] + v[i-1])  (假設 v 是 0-indexed, dp[0]=0, dp[1]=v[0])
        
        // 由於 M <= 1000，對每個員工每次檢查做 O(M) DP 是可以接受的。
        // 二分搜尋範圍：k 最小為 1，最大是多少？
        // 最壞情況：C=1e9, a[j]=1, w=1, M=1 (只能選一天)
        // 第 x 工期收入 = 1 + (x-1)*1 = x >= 1e9 => x ~ 1e9
        // 所以二分上界設為 2e9 足夠 (long long 範圍內)。
        
        // 但 N, M <= 1000, 如果對每個員工都二分 (log(2e9) ~ 31 次)，每次 O(M)，總複雜度 O(N * M * log(C_max))
        // 1000 * 1000 * 31 = 3.1e7，在 1 秒內應該可以通過。

        vector<int> results;
        results.reserve(N);

        for (int i = 0; i < N; ++i) {
            long long wi = w[i];
            
            // 二分搜尋最小工期數 x (x >= 1)
            long long low = 1, high = 2000000000LL; // 2e9
            long long ans = high;

            // 優化：如果第一個工期就達標
            // 先算一次 x=1 的情況 (K=0)
            vector<long long> dp(M + 1, 0);
            // dp[j] 表示前 j 天 (0..j-1) 的最大收益
            // v[k] = a[k] + 0 = a[k]
            if (M > 0) {
                dp[1] = a[0];
                for (int j = 2; j <= M; ++j) {
                    long long val = a[j-1]; // K=0
                    dp[j] = max(dp[j-1], dp[j-2] + val);
                }
            }
            if (dp[M] >= C) {
                results.push_back(1);
                continue;
            }

            while (low <= high) {
                long long mid = low + (high - low) / 2;
                long long K = (mid - 1) * wi;
                
                // 計算在 K 下的最大收益
                // v[j] = a[j] + K
                // dp[j] = max(dp[j-1], dp[j-2] + a[j-1] + K)
                // 注意：這裡 K 是常數，加在每個選中的天上
                // 我們可以重用上面的邏輯
                
                vector<long long> current_dp(M + 1, 0);
                if (M > 0) {
                    current_dp[1] = a[0] + K;
                    for (int j = 2; j <= M; ++j) {
                        long long val = a[j-1] + K;
                        current_dp[j] = max(current_dp[j-1], current_dp[j-2] + val);
                    }
                }
                
                if (current_dp[M] >= C) {
                    ans = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            results.push_back((int)ans);
        }

        for (int i = 0; i < N; ++i) {
            cout << results[i] << (i == N - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
