#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 使用 long long 防止總價值溢出，雖然題目範例不大，但保險起見
typedef long long ll;

void solve() {
    int T;
    if (!(cin >> T)) return;

    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        ll N, s1, v1, s2, v2;
        cin >> N >> s1 >> v1 >> s2 >> v2;

        // 處理體積為 0 的邊界情況（雖然題目通常不會出現，但防呆）
        if (s1 == 0 && s2 == 0) {
            cout << "Case #" << caseNum << ": " << 0 << endl;
            continue;
        }
        if (s1 == 0) {
            // 只有物品 2 有效
            cout << "Case #" << caseNum << ": " << (N / s2) * v2 << endl;
            continue;
        }
        if (s2 == 0) {
            // 只有物品 1 有效
            cout << "Case #" << caseNum << ": " << (N / s1) * v1 << endl;
            continue;
        }

        // 確定哪個物品性價比更高 (v/s)
        // 比較 v1/s1 和 v2/s2 -> 比較 v1*s2 和 v2*s1
        // best_idx 為 1 或 2
        int best_idx = 1;
        ll other_idx = 2;
        ll s_best = s1, v_best = v1;
        ll s_other = s2, v_other = v2;

        // 如果物品 2 的性價比 >= 物品 1，則交換，讓 best 總是性價比最高的
        // 注意：若相等，任選一個即可，這裡選 >= 讓邏輯統一
        if (v1 * s2 < v2 * s1) {
            best_idx = 2;
            other_idx = 1;
            s_best = s2; v_best = v2;
            s_other = s1; v_other = v1;
        }

        ll max_value = 0;

        // 核心策略：
        // 既然物品 Best 的性價比最高，理論上我們想盡量多拿 Best。
        // 但是，因為必須湊整數個數，可能會有剩餘空間浪費。
        // 有時候少拿幾個 Best，騰出的空間剛好能塞入多個 Other，反而總價值更高。
        // 根據數論性質，我們只需要檢查「少拿」Best 的數量從 0 到 s_other - 1 的情況即可覆蓋最優解。
        // 為什麼？因為如果我們少拿了 s_other 個 Best，騰出的體積是 s_other * s_best，
        // 這體積至少可以塞入 s_best 個 Other (因為 s_best * s_other = s_other * s_best)。
        // 由於 Best 的性價比 >= Other，用 s_other 個 Best 換 s_best 個 Other 絕對不划算（或相等）。
        // 因此，最優解中，Best 的數量對 s_other 取模後的「不足量」一定小於 s_other。
        // 也就是說，我們只需要枚舉 Best 的數量 k，使得 k 從 max_count 往下減，最多減 s_other 次。
        
        ll max_best_count = N / s_best;
        
        // 我們需要枚舉的範圍是：從 max_best_count 往下，直到 max_best_count - s_other
        // 但不能低於 0
        ll start_k = max_best_count;
        ll end_k = max(0LL, max_best_count - s_other); 
        // 為了保險起見，也限制循環次數不要超過 s_other + 1 次，避免 s_other 極大時超時
        // 實際上上面的 end_k 已經限制了範圍長度為 s_other + 1
        
        for (ll k = start_k; k >= end_k; --k) {
            ll remaining_vol = N - k * s_best;
            ll count_other = remaining_vol / s_other;
            ll current_value = k * v_best + count_other * v_other;
            if (current_value > max_value) {
                max_value = current_value;
            }
        }

        // 另外一種情況：如果 s_other 很小，而 s_best 很大，上面的循環次數可能還是太多嗎？
        // 不會，因為循環次數是 min(max_best_count, s_other)。
        // 如果 s_other 很大，循環次數由 s_other 決定？不對，是由 s_other 決定上限。
        // 等等，如果 s_other 非常大 (例如 10^9)，那循環會超時嗎？
        // 讓我們重新審視邏輯：
        // 我們枚舉的是「最佳物品」的數量。
        // 如果 s_other 很大，代表我們只需要檢查很少的幾種「替換」情況嗎？
        // 不，邏輯是：任何超過 s_other 數量的 Best 可以被替換為 s_best 數量的 Other 而不虧損（因為 Best 性價比高）。
        // 所以最優解中，Other 的數量一定小於 s_best 嗎？
        // 讓我們反過來想：
        // 假設最優解中有 x 個 Best 和 y 個 Other。
        // 如果 y >= s_best，那麼我們可以拿出 s_best 個 Other，騰出 s_best * s_other 的體積。
        // 這些體積可以放入 s_other 個 Best。
        // 比較價值變化：
        // 失去：y_part * v_other (其中 y_part = s_best)
        // 獲得：x_part * v_best (其中 x_part = s_other)
        // 因為 v_best/s_best >= v_other/s_other => v_best * s_other >= v_other * s_best
        // 所以替換後價值不會變低。
        // 結論：在最優解中，Other 的數量一定小於 s_best。
        // 所以我們應該枚舉 Other 的數量 (0 到 s_best - 1)，而不是 Best 的數量！
        // 除非 s_best 也很大？
        // 如果 s_best 和 s_other 都很大 (> sqrt(N))，那麼兩者數量都不會超過 sqrt(N)，直接枚舉任一者皆可。
        // 如果 s_best 很小，那麼枚舉 Other (0 到 s_best-1) 很快。
        // 如果 s_best 很大，那麼 Best 的數量本身就很少 (N/s_best 很小)，直接枚舉 Best 的數量也很快。
        
        // 修正後的魯棒策略：
        // 選擇枚舉數量較少的那個維度，或者利用上述數論性質。
        // 性質：最優解中，性價比低的物品 (Other) 數量一定 < s_best。
        // 所以我們只需要枚舉 Other 的數量 from 0 to min(N/s_other, s_best - 1)。
        // 這樣複雜度是 O(min(N/s_other, s_best))。
        // 如果 s_best 很大，這個範圍可能很大嗎？
        // 如果 s_best 很大，那麼 N/s_best 很小，代表 Best 的數量很少。
        // 這時候其實直接枚舉 Best 的數量 (0 到 N/s_best) 會更快。
        
        // 綜合策略：
        // 1. 如果 N/s_best < s_best (即 Best 的總可能數量 小於 s_best)，則直接枚舉 Best 的數量 (0 ~ N/s_best)。
        // 2. 否則，利用數論性質，枚舉 Other 的數量 (0 ~ s_best - 1)。
        // 這樣可以保证複雜度在 O(sqrt(N)) 級別。
        // 因為如果 s_best <= sqrt(N)，則第二種情況循環 <= sqrt(N)。
        // 如果 s_best > sqrt(N)，則第一種情況循環 N/s_best < N/sqrt(N) = sqrt(N)。
        
        max_value = 0;
        ll limit_best_count = N / s_best;
        
        if (limit_best_count < s_best) {
            // 情況 A: Best 的總數量本來就不多，直接全部枚舉
            for (ll k = 0; k <= limit_best_count; ++k) {
                ll rem = N - k * s_best;
                ll c_other = rem / s_other;
                ll val = k * v_best + c_other * v_other;
                if (val > max_value) max_value = val;
            }
        } else {
            // 情況 B: Best 的總數量很多，但根據數論，Other 的數量不需要超過 s_best
            // 我們枚舉 Other 的數量 i 從 0 到 s_best - 1
            ll limit_other = s_best; 
            // 當然也不能超過實際能裝的數量
            ll max_possible_other = N / s_other;
            if (limit_other > max_possible_other + 1) limit_other = max_possible_other + 1;

            for (ll i = 0; i < limit_other; ++i) {
                ll vol_used_other = i * s_other;
                if (vol_used_other > N) break;
                ll rem = N - vol_used_other;
                ll c_best = rem / s_best;
                ll val = c_best * v_best + i * v_other;
                if (val > max_value) max_value = val;
            }
        }

        cout << "Case #" << caseNum << ": " << max_value << endl;
    }
}

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
