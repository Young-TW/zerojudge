#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int X;
    if (!(cin >> X)) return 0;
    
    string N_str;
    cin >> N_str;

    // N_str 是 N 的十進位表示法，長度為 X
    // 我們需要計算 sum_{i=1}^{N} G(i) mod 998244353
    // G(i) 是 i 的前綴 1 的數量
    
    // 思路：
    // 對於每個位置 k (從左到右，0-indexed)，計算有多少個數字 i (1 <= i <= N) 
    // 使得 i 的前 k+1 位都是 1。
    // 如果一個數字 i 的前 m 位都是 1，那麼它會對 G(i) 貢獻 m。
    // 這等價於對每個 k (0 <= k < X)，計算有多少個 i <= N 使得 i 的前 k+1 位都是 1。
    // 然後將這些數量加總。

    // 對於固定的 k (0 <= k < X)，我們想計算有多少個 i (1 <= i <= N) 
    // 使得 i 的前 k+1 位都是 1。
    // 令 prefix_ones = 由 k+1 個 '1' 組成的字串。
    // 如果 N 的長度 X < k+1，則沒有這樣的數字。
    // 如果 X == k+1，則只有一個 candidate: prefix_ones 本身，檢查它是否 <= N。
    // 如果 X > k+1，則所有形如 prefix_ones + suffix 的數字都可能是 candidate，
    // 其中 suffix 是任意长度为 X - (k+1) 的數字（包括前導零），但要確保整體 <= N。
    
    // 更精確地說：
    // 對於位置 k (0-indexed, 代表第 k+1 位)，我們考慮前綴 P = "11...1" (k+1 個 1)。
    // 情況 1: k+1 > X: 不可能，貢獻為 0。
    // 情況 2: k+1 == X: 只有一個數字 P。如果 P <= N，則貢獻 1，否則 0。
    // 情況 3: k+1 < X: 
    //   我們構造數字 P 後面接上 (X - (k+1)) 位數字。
    //   設 L = X - (k+1)。
    //   這些數字的範圍是 [P * 10^L, P * 10^L + (10^L - 1)]。
    //   我們需要計算這個區間與 [1, N] 的交集大小。
    //   由於 P 是以 1 開頭且長度為 k+1，而 N 的長度為 X > k+1，所以 P * 10^L 的長度是 X。
    //   比較 P (作為長度 X 的數字，即 P * 10^L) 與 N 的前 k+1 位。
    //   令 N_prefix = N 的前 k+1 位。
    //   如果 P < N_prefix: 則所有以 P 開頭的 X 位數都小於 N。共有 10^L 個。
    //   如果 P > N_prefix: 則沒有以 P 開頭的 X 位數小於等於 N。共有 0 個。
    //   如果 P == N_prefix: 則以 P 開頭且小於等於 N 的數字個數為 (N mod 10^L) + 1。
    //      這裡 N mod 10^L 是 N 的後 L 位構成的數字。
    
    // 注意：我們還必須考慮長度小於 X 的數字。
    // 上面的邏輯只處理了長度為 X 的數字。
    // 對於長度 len < X 的數字：
    //   如果 len < k+1: 無法有 k+1 個前綴 1，貢獻 0。
    //   如果 len == k+1: 只有一個數字 "11...1" (len 個 1)。因為 len < X 且 N 有 X 位，所以這個數字一定小於 N。貢獻 1。
    //   如果 len > k+1: 但我們現在考慮的是長度 len < X 的數字，所以這情況不會發生在 len < X 的範疇內，除非 k+1 < len < X。
    //   等等，我的邏輯有點混亂。讓我們重新整理。

    // 重新思考：
    // 總和 = sum_{k=0}^{X-1} (有多少個 i in [1, N] 使得 i 的前 k+1 位都是 1)
    // 對於固定的 k，我們要計算 count(k) = |{ i in [1, N] : i 的前 k+1 位都是 1 }|
    // i 的位數可以是 len，其中 k+1 <= len <= X。
    // 如果 len < k+1，則 i 不可能有 k+1 個前綴 1。
    
    // 對於固定的 k 和固定的長度 len (k+1 <= len <= X):
    //   如果 len < X:
    //     我們需要構造一個 len 位數，前 k+1 位是 1。
    //     這樣的數字形式為 "11...1" (k+1 個) + 任意 (len - k - 1) 位數字。
    //     共有 10^(len - k - 1) 個這樣的數字。
    //     因為 len < X，這些數字都小於 N (因為 N 有 X 位)。
    //     所以貢獻為 10^(len - k - 1)。
    //   如果 len == X:
    //     我們需要構造一個 X 位數，前 k+1 位是 1，且 <= N。
    //     令 P = "11...1" (k+1 個 1)。
    //     令 L = X - (k+1)。
    //     如果 L < 0: 不可能 (已排除，因為 len >= k+1)。
    //     如果 L == 0: 則數字就是 P。檢查 P <= N? 是則 1，否則 0。
    //     如果 L > 0:
    //       比較 P 與 N 的前 k+1 位 (N_prefix)。
    //       如果 P < N_prefix: 所有 10^L 個數字都符合。
    //       如果 P > N_prefix: 沒有數字符合。
    //       如果 P == N_prefix: 則有 (N_suffix + 1) 個數字符合，其中 N_suffix 是 N 的後 L 位。
    
    // 算法：
    // ans = 0
    // for k from 0 to X-1:
    //   current_count = 0
    //   for len from k+1 to X:
    //     if len < X:
    //       ways = pow(10, len - k - 1, MOD)
    //       current_count = (current_count + ways) % MOD
    //     else: // len == X
    //       L = X - (k+1)
    //       if L < 0: continue (不會發生)
    //       string P(k+1, '1')
    //       if L == 0:
    //         if P <= N_str: current_count = (current_count + 1) % MOD
    //       else:
    //         string N_prefix = N_str.substr(0, k+1)
    //         if P < N_prefix:
    //           ways = pow(10, L, MOD)
    //           current_count = (current_count + ways) % MOD
    //         else if P > N_prefix:
    //           // 0
    //         else: // P == N_prefix
    //           string N_suffix_str = N_str.substr(k+1)
    //           // 將 N_suffix_str 轉為數字 mod MOD
    //           long long N_suffix = 0
    //           for char c : N_suffix_str:
    //             N_suffix = (N_suffix * 10 + (c - '0')) % MOD
    //           ways = (N_suffix + 1) % MOD
    //           current_count = (current_count + ways) % MOD
    //   ans = (ans + current_count) % MOD

    // 優化：
    // 內層迴圈 for len from k+1 to X-1 是一個等比級數。
    // sum_{j=0}^{X-k-2} 10^j = (10^(X-k-1) - 1) / 9
    // 但我們要小心邊界條件和模運算。
    // 或者直接迭代計算，因為 X <= 1000，O(X^2) 是可以接受的。
    // 1000^2 = 1e6，非常安全。

    auto power = [](long long base, long long exp) -> long long {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    };

    long long total_ans = 0;

    for (int k = 0; k < X; ++k) {
        // k 代表前綴長度減 1，即我們檢查前 k+1 位是否為 1
        int prefix_len = k + 1;
        long long count_k = 0;

        // 考慮長度 len 從 prefix_len 到 X
        for (int len = prefix_len; len <= X; ++len) {
            if (len < X) {
                // 長度為 len 的數字，前 prefix_len 位是 1
                // 剩餘位数 = len - prefix_len
                int remaining_digits = len - prefix_len;
                long long ways = power(10, remaining_digits);
                count_k = (count_k + ways) % MOD;
            } else {
                // len == X
                int L = X - prefix_len; // 後綴長度
                string P(prefix_len, '1');
                
                if (L == 0) {
                    // P 的長度等於 X
                    if (P <= N_str) {
                        count_k = (count_k + 1) % MOD;
                    }
                } else {
                    string N_prefix = N_str.substr(0, prefix_len);
                    if (P < N_prefix) {
                        long long ways = power(10, L);
                        count_k = (count_k + ways) % MOD;
                    } else if (P == N_prefix) {
                        string N_suffix_str = N_str.substr(prefix_len);
                        long long N_suffix = 0;
                        for (char c : N_suffix_str) {
                            N_suffix = (N_suffix * 10 + (c - '0')) % MOD;
                        }
                        long long ways = (N_suffix + 1) % MOD;
                        count_k = (count_k + ways) % MOD;
                    }
                    // if P > N_prefix, add 0
                }
            }
        }
        total_ans = (total_ans + count_k) % MOD;
    }

    cout << total_ans << endl;

    return 0;
}
