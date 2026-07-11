#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int N;
vector<long long> d;
int idx;

// 返回 pair<min_degree, max_degree> 對於當前子樹
pair<long long, long long> solve() {
    if (idx >= N) {
        return {0, 0};
    }

    long long val = d[idx++];
    
    // 如果當前節點值為 0，則是葉節點（枯枝結束）
    // 根據題目定義，枯枝程度計算需要左右子樹
    // 若 val == 0，表示沒有子樹，枯枝程度即為 0? 
    // 但根據範例推導：
    // 範例 1: 1 2 0 -> 結構可能是 1 -> 2 -> 0 (鏈狀) 或 1 有子節點 2, 2 有子節點 0
    // 讓我們重新理解題目：
    // "樹的枯枝程度 = max(左子樹的枯枝程度, 右子樹的枯枝程度) + 根樹枝的枯枝值"
    // 輸入是前序走訪。0 代表該分支結束（無子節點）。
    // 當遇到 0 時，它是一個葉節點，其左右子樹皆空，枯枝程度為 0。
    // 但這個 0 本身是 "根樹枝的枯枝值" 嗎？
    // 題目說 di 是枯枝值。若 di=0，則該節點貢獻為 0。
    // 關鍵在於如何構建樹。前序走訪中，0 通常表示該位置沒有子樹（空指針）。
    // 但在本題中，0 是序列的一部分，且是非負整數。
    // 觀察範例 1: 3 個節點 1, 2, 0。輸出 3 3。
    // 若結構是 1 (左: 2 (左: 0, 右: null), 右: null)
    // 節點 0: left=0, right=0 -> deg = max(0,0)+0 = 0
    // 節點 2: left=0, right=0 (假設 0 是左子，右子空) -> deg = max(0, 0) + 2 = 2? 不對，因為 0 已經消耗了一個節點。
    // 讓我們換個思路：這是一個二元樹的前序遍歷，其中 0 代表「空子樹」嗎？
    // 不，題目說 N 段樹枝，di 是枯枝值。0 也是枯枝值。
    // 如果是標準的二元樹重建，通常需要知道何時停止。
    // 這裡的規則可能是：每個非零節點必須有兩個子節點（或是遞迴直到消耗完所有節點？）
    // 或者，0 代表葉節點的標記？
    // 再看範例 2: 7 個節點 3 1 1 0 2 0 5。
    // 若 0 代表空子樹（null），則序列解讀為：
    // Root=3
    //   Left=1
    //     Left=1
    //       Left=0 (null)
    //       Right=2
    //         Left=0 (null)
    //         Right=5
    //   Right=? 節點不夠了。
    // 這表示 0 不是 null，而是一個實際的節點，其值為 0。
    // 那麼如何決定樹的結構？
    // 題目問的是「滿足條件的園藝用造景樹中」，暗示樹的結構不唯一，我們可以選擇如何將序列組合成樹。
    // 限制條件是什麼？前序走訪順序固定。
    // 二元樹的前序走訪：Root, Left_Subtree, Right_Subtree。
    // 我們需要將序列 d[idx...N-1] 分割成 Root, Left_Part, Right_Part。
    // Root 是 d[idx]。
    // Left_Part 和 Right_Part 是非空的嗎？不一定。
    // 但題目說 N 段樹枝，應該每個數字都對應一個節點。
    // 問題轉化為：給定前序序列，有多少種方式將其切割成合法的二元樹？
    // 對於一個節點，它可以有：
    // 1. 無子節點（葉節點）：消耗 1 個節點。
    // 2. 只有左子節點：消耗 1 + size(left)。
    // 3. 只有右子節點：消耗 1 + size(right)。
    // 4. 左右都有：消耗 1 + size(left) + size(right)。
    // 但是，前序走訪無法區分「只有左」和「只有右」的情況，除非我們知道子樹的大小。
    // 實際上，對於給定的前序序列，若沒有其他資訊（如中序），樹的結構是不確定的。
    // 本题正是要我們枚舉所有可能的樹結構，找出枯枝程度的最小值和最大值。
    // 定義 DP 或遞迴：
    // f(i, j) = 使用 d[i...j] 這段序列能構成的所有樹的 {min_deg, max_deg}
    // 但這太慢 O(N^3) 或更多。N=1000，需要 O(N^2) 或 O(N)。
    // 觀察遞迴式：deg = max(deg_L, deg_R) + val
    // 要使 deg 最小：我們希望 max(deg_L, deg_R) 盡量小。
    // 要使 deg 最大：我們希望 max(deg_L, deg_R) 盡量大。
    // 由於是前序，Root 固定在 i。剩下的 i+1 ... j 要分給 Left 和 Right。
    // 設 Left 佔用 k 個節點 (i+1 ... i+k)，Right 佔用 j-(i+k) 個節點。
    // 我们需要遍历所有可能的 k。
    // 狀態：dp_min[i][j], dp_max[i][j] 表示區間 [i, j] 的最小/最大枯枝程度。
    // 轉移：
    // Root = d[i]
    // 若 i == j: 葉節點，deg = d[i] (因為左右子樹为空，max(0,0)=0? 還是葉節點定義不同？)
    // 根據公式：deg = max(left_deg, right_deg) + root_val
    // 若無子樹，left_deg = 0, right_deg = 0? 那麼 deg = root_val.
    // 驗證範例 1: 1 2 0
    // 可能結構：
    // A: 1 (L: 2 (L: 0), R: null) -> 0: deg=0; 2: deg=max(0,0)+2=2; 1: deg=max(2,0)+1=3.
    // B: 1 (L: null, R: 2 (L: 0)) -> 同上 3.
    // C: 1 (L: 2, R: 0) -> 2: deg=2; 0: deg=0; 1: deg=max(2,0)+1=3.
    // D: 1 (L: 2 (R: 0), R: null) -> 3.
    // 似乎都是 3。
    // 範例 2: 3 1 1 0 2 0 5 (N=7)
    // 目標 min=8, max=12.
    // 若全左斜：3->1->1->0->2->0->5? 不行，前序必須符合結構。
    // 讓我們用區間 DP。
    // dp_min[i][j]: 區間 [i, j] 構成樹的最小枯枝程度
    // dp_max[i][j]: 區間 [i, j] 構成樹的最大枯枝程度
    // 基礎情況：i == j, dp[i][i] = d[i]
    // 轉移：枚舉左子樹的結束位置 k (從 i 到 j-1)
    // 左子樹區間 [i+1, k], 右子樹區間 [k+1, j]
    // 注意：左子樹或右子樹可以為空嗎？
    // 如果左子樹為空，則區間 [i+1, k] 不存在，k = i。此時右子樹為 [i+1, j]
    // 如果右子樹為空，則 k = j。此時左子樹為 [i+1, j]
    // 如果都非空，則 i+1 <= k < j
    // 對於空子樹，其枯枝程度視為 0。
    // 所以：
    // for k from i to j:
    //   left_deg = (k == i) ? 0 : dp[k][i+1...k] (注意索引)
    //   right_deg = (k == j) ? 0 : dp[k+1...j]
    //   current = max(left_deg, right_deg) + d[i]
    //   update min/max
    
    // 複雜度：O(N^3)。N=1000 -> 10^9 太大。
    // 需要優化。
    // 觀察性質：
    // deg = max(L, R) + V
    // 要最大化：讓較大的那個子樹盡量大。
    // 要最小化：讓兩個子樹盡量平衡且小？或者讓其中一個為 0？
    // 其實，對於最大值，我們總是希望把大的值累積起來。
    // 對於最小值，我們希望避免 max(L, R) 過大。
    // 是否有貪心策略？
    // 考慮最大值：
    // max_deg(i, j) = d[i] + max( max_deg(i+1, k), max_deg(k+1, j) ) 對所有 k 取最大
    // 顯然，為了讓 max(...) 最大，我們應該讓其中一個子樹包含整個區間 [i+1, j]，另一個為空。
    // 因為如果拆分，max(A, B) <= max(A+B 的某種組合)? 不一定。
    // 但直覺上，將所有節點串成一條鏈（每次只選一邊）會讓深度最深，累加最多。
    // 例如：Root + max(Chain(i+1...j), 0) = Root + Chain(i+1...j)
    // 這樣遞迴下去，就是所有節點之和？
    // 範例 2 sum = 3+1+1+0+2+0+5 = 12。輸出最大值正是 12。
    // 範例 1 sum = 3。輸出 3。
    // 範例 3 sum = 1+2+3+0+2+3+3+0+2+5 = 21。輸出最大值 21。
    // 結論：最大值一定是所有節點總和（構造為單鏈）。
    
    // 現在看最小值。
    // 我們希望 max(L, R) 盡量小。
    // 這類似於將序列切成兩半，使兩邊的「枯枝程度」最大值最小。
    // 這是一個經典的 DP 優化問題嗎？
    // 或者有更簡單的性質？
    // 注意到 d[i] >= 0。
    // 如果我們將區間 [i+1, j] 分成兩部分，使得兩部分的枯枝程度盡量接近？
    // 但枯枝程度不是和，而是 max(...)+val 的遞迴結構。
    // 讓我們重新思考最小值的結構。
    // 對於區間 [i, j]，root = d[i]。
    // 我們需要選擇 split point k，使得 max(min_deg(i+1, k), min_deg(k+1, j)) 最小。
    // 這裡 min_deg(empty) = 0。
    // 這個函數 min_deg(i, j) 是否具有單調性？
    // 當區間變大時，min_deg 單調不減？是的，因為 d >= 0。
    // 所以，隨著 k 增加，左邊 min_deg(i+1, k) 單調增加，右邊 min_deg(k+1, j) 單調減少。
    // 我們要找 k 使得 max(Left(k), Right(k)) 最小。
    // 這發生在 Left(k) 和 Right(k) 最接近的時候。
    // 我們可以使用雙指針或二分搜尋來找到最佳的 k。
    // 這樣可以將轉移優化到 O(1) 或 O(log N)，總複雜度 O(N^2)。
    // N=1000，O(N^2) = 10^6，完全可以接受。
    
    // 實作細節：
    // 用 len 從 1 到 N 枚舉區間長度。
    // i 從 0 到 N-len。j = i+len-1。
    // 計算 dp_min[i][j]。
    // 對於最大值，直接 sum[i...j] 即可？
    // 驗證：max_deg(i, j) = sum(i, j)。
    // 證明：max_deg = d[i] + max(max_deg(L), max_deg(R))。
    // 若 L 為空，R 為 full，則 = d[i] + max_deg(R) = d[i] + sum(R) = sum(i, j)。
    // 若拆分，max(sum(L), sum(R)) <= sum(L)+sum(R) = sum(i+1, j)。
    // 所以 max_deg(i, j) = d[i] + sum(i+1, j) = sum(i, j)。
    // 正確。最大值就是區間和。
    
    // 所以只需 DP 求最小值。
    // dp_min[i][j] = d[i] + min_{k=i..j} ( max( (k==i ? 0 : dp_min[i+1][k]), (k==j ? 0 : dp_min[k+1][j]) ) )
    // 由於單調性，我們可以維護一個指針 k，隨著 j 增加或 i 變化？
    // 對於固定的 i, j，當 k 從 i 增加到 j：
    // Left(k) = dp_min[i+1][k] (單調增)
    // Right(k) = dp_min[k+1][j] (單調減)
    // 我們要找 k 使 max(Left, Right) 最小。
    // 可以在 O(len) 內線性掃描，總複雜度 O(N^3)？
    // 1000^3 = 10^9，有點危險，但常數很小（內部只是比較和賦值）。
    // 或者用雙指針優化？
    // 對於固定 i，當 j 增加時，最佳 k 也會向右移動？
    // 是的，典型的決策單調性。
    // 但為了保險起見，先寫 O(N^3) 看看？不，10^9 在 1 秒內可能過不了。
    // 必須優化到 O(N^2)。
    // 對於每個區間 [i, j]，我們可以用雙指針找最佳 k。
    // 但每個區間都要找一次，還是 O(N^3)？
    // 不，對於固定 i，當 j 增加時，最佳 k 單調遞增。
    // 所以對於每個 i，我們可以用一個指針 k 掃描 j，均攤 O(N)。
    // 總複雜度 O(N^2)。
    
    // 實作：
    // 外層 len: 1 -> N
    // 中層 i: 0 -> N-len
    // j = i+len-1
    // 內層找 k：
    // 由於 len 從小到大，當計算 [i, j] 時，[i+1, k] 和 [k+1, j] 都已計算過。
    // 對於固定 i, j，我們需要掃描 k。
    // 但如果我們利用單調性：
    // 對於固定 i，當 j 增加時，最佳 k (記為 best_k[i][j]) 不會小於 best_k[i][j-1]。
    // 所以我們可以記錄 best_k[i]，隨著 j 增加而更新。
    // 這樣內層循環均攤 O(1)。
    
    // 讓我們用簡單的方式：對於每個 [i, j]，用雙指針或二分找 k。
    // 由於 N=1000，O(N^2 log N) 也可以。
    // 或者直接在 k 上線性掃描，但剪枝：
    // 當 Left(k) > Right(k) 時，再增加 k 只會讓 Left 更大，Right 更小，max 會變大（或持平）。
    // 所以一旦 Left(k) >= Right(k)，我們就可以停止，並比較當前 k 和 k-1。
    // 這樣平均很快。
    
    // 讓我們實作 O(N^2) 的 DP，內層用線性掃描但提前終止。
}

int main() {
    while (cin >> N) {
        d.resize(N);
        for (int i = 0; i < N; ++i) {
            cin >> d[i];
        }

        vector<vector<long long>> dp_min(N, vector<long long>(N));
        vector<vector<long long>> sum(N, vector<long long>(N, 0));

        // 預處理區間和
        for (int i = 0; i < N; ++i) {
            long long s = 0;
            for (int j = i; j < N; ++j) {
                s += d[j];
                sum[i][j] = s;
            }
        }

        // DP
        for (int len = 1; len <= N; ++len) {
            for (int i = 0; i <= N - len; ++i) {
                int j = i + len - 1;
                if (len == 1) {
                    dp_min[i][j] = d[i];
                } else {
                    long long best = LLONG_MAX;
                    // 枚舉左子樹的結束位置 k
                    // 左子樹區間 [i+1, k], 右子樹 [k+1, j]
                    // k 從 i (左空) 到 j (右空)
                    // 優化：由於 Left(k) 單調增，Right(k) 單調減
                    // 當 Left(k) >= Right(k) 時，後續的 k 不會更優（因為 Left 會繼續增，Right 繼續減，max 由 Left 決定且變大）
                    // 所以我們只需要檢查到第一個 Left(k) >= Right(k) 的位置，並比較該點和前一點。
                    
                    int best_k = -1;
                    for (int k = i; k <= j; ++k) {
                        long long left_deg = (k == i) ? 0 : dp_min[i+1][k];
                        long long right_deg = (k == j) ? 0 : dp_min[k+1][j];
                        long long cur = max(left_deg, right_deg);
                        
                        if (cur < best) {
                            best = cur;
                        }
                        
                        // 剪枝：如果 left_deg 已經大於等於 right_deg，再往右 k 只會讓 left 更大
                        if (left_deg >= right_deg) {
                            break;
                        }
                    }
                    dp_min[i][j] = best + d[i];
                }
            }
        }

        cout << dp_min[0][N-1] << " " << sum[0][N-1] << endl;
        
        d.clear();
    }
    return 0;
}
