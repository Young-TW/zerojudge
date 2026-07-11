#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Tree {
    int id;
    long long x, y, h;
    double dist_sq; // 使用距離平方避免開根號的誤差與效能損失，比較大小時等效
};

// 計算兩點距離平方
long long dist_sq(long long x1, long long y1, long long x2, long long y2) {
    long long dx = x1 - x2;
    long long dy = y1 - y2;
    return dx * dx + dy * dy;
}

int main() {
    // 加速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N) {
        vector<Tree> trees(N);
        for (int i = 0; i < N; ++i) {
            trees[i].id = i;
            cin >> trees[i].x >> trees[i].y >> trees[i].h;
            // 計算與起點 (樹木 0，題目說 t1 在 0,0，但輸入順序不一定是 t1 在第一筆)
            // 題目說明：桑妮的家 t1 位於 (0, 0)，而桑妮的奶奶家 tN 位於 (10000, 10000)
            // 輸入格式：接下來的 N 列...代表第 i 棵樹 ti
            // 這裡要注意：題目的 t1, tN 是指邏輯上的編號，還是輸入的順序？
            // 通常這類題目 t1 對應輸入的第一棵樹 (index 0)，tN 對應最後一棵 (index N-1)。
            // 但題目又明確給了座標。讓我們假設輸入的第 1 棵樹就是起點，第 N 棵樹就是終點。
            // 並且題目說 "d(t1, tp(i+1)) 不小於 d(t1, tp(i))"，這裡的 t1 是起點。
            // 我們先以輸入順序為準，第 0 個元素是起點，第 N-1 個元素是終點。
            // 為了嚴謹，我們計算每個點到 "起點" (輸入的第一棵樹) 的距離。
            // 等等，題目說 "桑妮的家 t1 位於 (0, 0)"，這可能意味著我們需要找到座標為 (0,0) 的樹作為起點？
            // 不，通常 "第 i 棵樹 ti" 意味著輸入順序即為編號。第一行輸入的是 t1，最後一行是 tN。
            // 讓我們假設 index 0 是起點，index N-1 是終點。
            // 距離是相對於起點 (index 0) 的距離。
        }

        long long start_x = trees[0].x;
        long long start_y = trees[0].y;

        for (int i = 0; i < N; ++i) {
            trees[i].dist_sq = dist_sq(trees[i].x, trees[i].y, start_x, start_y);
        }

        // 排序規則：
        // 1. 距離起點的距離由小到大。
        // 2. 如果距離相同，題目沒有明確規定順序，但為了 DP 的正確性，我們需要確保在處理某個距離時，
        //    所有小於該距離的狀態已經計算完畢。
        //    對於距離相同的點，它們之間可以互相跳躍嗎？
        //    題目條件：d(t1, tp(i+1)) >= d(t1, tp(i))。允許相等。
        //    如果距離相等，A 可以跳到 B，B 也可以跳到 A。這會形成環嗎？
        //    如果 A->B (距離相等) 且 B->A (距離相等)，則可能無限循環？
        //    但題目要求 "相異樹木構成的序列"，所以不能重複訪問。
        //    不過我們的 DP 狀態是 dp[i] = 到達樹木 i 時累積的最大樂趣。
        //    如果距離相等，我們可能需要特殊處理。
        //    考慮到樂趣值 max(0, h_prev - h_curr) 永遠非負。
        //    如果距離相等，我們希望先處理高度較高的點，這樣它可以更新高度較低的點（產生樂趣）。
        //    如果先處理低的，高的還沒算好，就無法從高的跳下來獲得樂趣。
        //    所以排序第二關鍵字：高度由高到低。這樣在相同距離下，高的點先被處理，可以更新低的點。
        
        sort(trees.begin(), trees.end(), [](const Tree& a, const Tree& b) {
            if (a.dist_sq != b.dist_sq) {
                return a.dist_sq < b.dist_sq;
            }
            return a.h > b.h; 
        });

        // 現在 trees 已經排序。我們需要找到原來的起點和終點在排序後的位置嗎？
        // 不需要，我們只需要知道起點的初始狀態，並最終讀取終點的狀態。
        // 但 DP 是基於排序後的順序進行的。
        // 我們需要一個映射或直接使用排序後的陣列進行 DP。
        // 由於我們要輸出的是從起點到終點的最大樂趣，我們需要識別哪一個是終點。
        // 讓我們在排序前記錄終點的原始索引，或者在排序後遍歷尋找終點（通過座標或原始 ID）。
        // 這裡我們用原始 ID 來識別。起點 ID 是 0，終點 ID 是 N-1。
        
        int original_start_id = 0;
        int original_end_id = N - 1;

        // dp[i] 表示到達排序後第 i 棵樹時的最大累積樂趣
        // 初始化為 -1 表示不可達，或者 0？
        // 起點的樂趣是 0。其他點初始為 -infinity 或標記為不可達。
        // 由於樂趣是非負的，初始化為 -1 即可表示不可達。
        vector<long long> dp(N, -1);

        // 找到起點在排序後陣列中的位置並初始化
        // 由於可能有多个點距離相同（包含起點自己，距離為 0），我们需要小心。
        // 起點的距離一定是 0。如果有其他點也在 (0,0)，它們距離也是 0。
        // 根據排序規則，距離相同時高度高的在前。
        
        // 我們遍歷排序後的陣列來進行 DP
        // 但首先，我們需要將起點的 dp 值設為 0。
        // 由於我們不知道起點在哪裡，我們可以先找出來，或者在迴圈中判斷。
        
        // 更好的方法：
        // 建立一個從 original_id 到 sorted_index 的映射？或者直接遍歷。
        // 因為 N <= 100,000，O(N^2) 會超時。我們需要 O(N log N) 或 O(N)。
        // 目前的排序是 O(N log N)。DP 過程如果是對每個點檢查所有前面的點，那就是 O(N^2)。
        // 這不行。我们需要優化轉移過程。
        
        // 轉移方程：
        // dp[current] = max(dp[prev] + max(0, h[prev] - h[current]))
        // 條件：dist[prev] <= dist[current] (已通過排序保證，只要 prev 在 current 前面且滿足距離條件)
        // 注意：排序後，對於當前的 i，所有 j < i 滿足 dist[j] <= dist[i]。
        // 但如果 dist[j] == dist[i]，由於我們按高度降序排列，j 的高度 >= i 的高度。
        // 這時 max(0, h[j] - h[i]) = h[j] - h[i]。
        // 如果 dist[j] < dist[i]，則 h[j] 可能大於或小於 h[i]。
        
        // 我們需要快速查詢：
        // 1. max(dp[j]) 其中 dist[j] < dist[i] (或者 <=，但在同一組距離內我們單獨處理)
        // 2. max(dp[j] + h[j]) 其中 dist[j] < dist[i]
        // 因為 dp[i] = max( 
        //      max_{j: dist[j] <= dist[i], h[j] >= h[i]} (dp[j] + h[j] - h[i]),
        //      max_{j: dist[j] <= dist[i], h[j] < h[i]} (dp[j])
        //    )
        // 這可以重寫為：
        // dp[i] = max( 
        //      (max_{j: valid, h[j] >= h[i]} (dp[j] + h[j])) - h[i],
        //      (max_{j: valid, h[j] < h[i]} (dp[j]))
        //    )
        
        // 這是一個經典的數據結構問題。我們可以依序處理點（按距離分組）。
        // 對於每一組相同距離的點，它們之間的轉移需要小心（因為排序是按高度降序，所以前面的可以轉移到後面的）。
        // 但在處理完這一組之後，才將這一組的結果加入到全局數據結構中，以供下一組距離更大的點使用。
        // 這樣就避免了同一距離內的點被錯誤地多次利用（雖然題目允許同距離跳躍，但由於我們排序了，同距離內高度高的先處理，可以更新高度低的，這符合邏輯。但為了簡單起見，我們可以將同距離視為一層，層內可以轉移，層間也可以轉移）。
        // 其實，由於我們排序是同距離按高度降序，當處理到 i 時，所有 j < i 且 dist[j] == dist[i] 的點，其 h[j] >= h[i]。
        // 所以對於同距離的點，只能從高跳到低（或等高），樂趣為 h[j] - h[i]。
        // 這正好符合公式 dp[j] + h[j] - h[i]。
        // 所以我們不需要特別分層，只要保證在查詢時，數據結構中包含所有 j < i 的點即可？
        // 不行，因為如果 dist[j] == dist[i]，它們是可以互相轉移的。但我們的排序順序保證了如果 j < i 且 dist 相等，則 h[j] >= h[i]。
        // 所以 j 可以轉移到 i。但 i 不能轉移到 j (因為 h[i] <= h[j]，如果要轉移，樂趣是 0，但方向反了？不，題目只要求距離不減。如果距離相等，A->B 和 B->A 都合法。但我們排序後只考慮 j->i (j<i)。如果 B->A 合法且更優，我們會漏掉嗎？
        // 如果 A 和 B 距離相等，h[A] > h[B]。排序後 A 在 B 前面。A->B 合法，樂趣 h[A]-h[B]。
        // B->A 也合法（距離相等），樂趣 max(0, h[B]-h[A]) = 0。
        // 顯然 A->B 比 B->A 好（除非 dp[B] 原本就比 dp[A]+h[A]-h[B] 大，但這不可能，因為 dp[B] 至少可以從 A 轉移過來）。
        // 所以我們只需要考慮 j < i 的情況即可。排序順序已經幫我們處理了同距離的最佳轉移方向（高到低）。
        
        // 所以問題簡化為：
        // 維護一個數據結構，支持：
        // 1. 插入一個點 (h, val = dp, val_plus_h = dp + h)
        // 2. 查詢所有已插入點中：
        //    a. max(val_plus_h) 其中 h_query <= h_inserted (即 h_inserted >= h_current) -> 用於計算 h[j] >= h[i] 的情況
        //    b. max(val) 其中 h_inserted < h_current
        // 其實可以合併：
        // dp[i] = max( 
        //    query_max_val_plus_h(h[i], MAX_H) - h[i], 
        //    query_max_val(0, h[i]-1)
        // )
        // 這裡 query_max_val_plus_h(L, R) 返回高度在 [L, R] 範圍內的 max(dp[j] + h[j])
        // query_max_val(L, R) 返回高度在 [L, R] 範圍內的 max(dp[j])
        
        // 由於高度 h <= 100,000，我們可以使用線段樹或樹狀數組 (Fenwick Tree)。
        // 樹狀數組適合求前綴最大值。
        // 對於 max(dp[j] + h[j]) where h[j] >= h[i]：這是後綴最大值。可以用樹狀數組維護後綴，或者將高度反轉。
        // 對於 max(dp[j]) where h[j] < h[i]：這是前綴最大值。
        
        // 定義兩個樹狀數組：
        // BIT1: 維護 max(dp[j] + h[j])，索引為高度。查詢區間 [h[i], MAX_H] 的最大值。
        //       為了用前綴樹狀數組實現後綴查詢，我們可以將高度映射為 MAX_H - h + 1。
        // BIT2: 維護 max(dp[j])，索引為高度。查詢區間 [1, h[i]-1] 的最大值。
        
        const int MAX_H = 100005;
        
        // Fenwick Tree for Prefix Max
        struct FenwickTreeMax {
            int size;
            vector<long long> tree;
            FenwickTreeMax(int n) : size(n), tree(n + 1, -1) {}
            
            void update(int idx, long long val) {
                for (; idx <= size; idx += idx & -idx) {
                    tree[idx] = max(tree[idx], val);
                }
            }
            
            long long query(int idx) {
                long long res = -1;
                for (; idx > 0; idx -= idx & -idx) {
                    res = max(res, tree[idx]);
                }
                return res;
            }
        };

        // BIT2: prefix max for dp[j] on range [1, h[i]-1]
        FenwickTreeMax bit_dp(MAX_H);
        
        // BIT1: suffix max for dp[j] + h[j] on range [h[i], MAX_H]
        // 我們將高度 h 映射為 MAX_H - h + 1，這樣 [h, MAX_H] 變成 [1, MAX_H - h + 1] 的前綴
        FenwickTreeMax bit_dp_plus_h(MAX_H);

        // 我們需要知道起點在哪裡來初始化。
        // 遍歷排序後的陣列，找到 original_id == 0 的點。
        int start_idx = -1;
        int end_idx = -1;
        
        for(int i=0; i<N; ++i){
            if(trees[i].id == original_start_id) start_idx = i;
            if(trees[i].id == original_end_id) end_idx = i;
        }
        
        // 初始化起點
        // 注意：起點可能在排序後的任何位置（雖然距離是 0，通常在很前面，但如果有其他點也在 (0,0) 且高度更高，則會在前面）
        // 我們不能在迴圈外直接初始化，因為要確保在處理起點之前，數據結構是空的（或者只包含距離更小的點，但起點距離最小為 0）。
        // 實際上，距離為 0 的點只有起點自己（如果有其他點也在 (0,0)，它們距離也是 0）。
        // 如果有多個點在 (0,0)，它們之間可以互相跳躍。
        // 但起點必須是旅程的第一個點 p(1)=1。所以其他點不能跳到起點。
        // 所以起點的 dp 值固定為 0，且不能從其他點轉移而來。
        // 我們在迴圈中遇到起點時，強制設定 dp = 0，並忽略從數據結構查詢的結果。
        
        for (int i = 0; i < N; ++i) {
            long long current_h = trees[i].h;
            long long best = -1;

            bool is_start = (trees[i].id == original_start_id);

            if (!is_start) {
                // Query 1: max(dp[j]) where h[j] < current_h
                if (current_h > 1) {
                    long long q1 = bit_dp.query(current_h - 1);
                    if (q1 != -1) best = max(best, q1);
                }

                // Query 2: max(dp[j] + h[j]) where h[j] >= current_h
                // Map height: idx = MAX_H - current_h + 1
                int mapped_idx = MAX_H - current_h + 1;
                long long q2 = bit_dp_plus_h.query(mapped_idx);
                if (q2 != -1) {
                    best = max(best, q2 - current_h);
                }
            } else {
                best = 0; // 起點的樂趣為 0
            }

            if (best != -1) {
                dp[i] = best;
                
                // Update data structures
                // Only update if this node is reachable (which it is if best != -1)
                // But wait, can we jump from a node that is not the start but has dp != -1? Yes.
                
                // Update BIT2: dp[i] at height current_h
                bit_dp.update(current_h, dp[i]);
                
                // Update BIT1: dp[i] + h[i] at height current_h (mapped)
                int mapped_idx = MAX_H - current_h + 1;
                bit_dp_plus_h.update(mapped_idx, dp[i] + current_h);
            }
        }

        // 找出終點的 dp 值
        long long ans = 0;
        if (end_idx != -1 && dp[end_idx] != -1) {
            ans = dp[end_idx];
        } else {
            // 理論上應該總有路徑，因為起點和終點存在，且可以直飛（如果距離條件允許）
            // 起點距離 0，終點距離 > 0，所以可以直接跳。
            // 除非 N=1? 題目說 K > 1，所以 N >= 2。
            // 如果終點不可達，可能是邏輯錯誤。但在本題設定下應該不會發生。
            // 若真的不可達，輸出 0 或其他？題目保證有解嗎？
            // 假設有解。
            ans = 0; 
        }

        cout << ans << "\n";
    }

    return 0;
}
