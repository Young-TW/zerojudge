#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定義模數 P = 10^9 + 7
const long long MOD = 1000000007LL;

// 快速冪函數：計算 (base^exp) % mod
// 用於計算總乘積的模逆元 (費馬小定理)
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % MOD;
        base = (__int128)base * base % MOD;
        exp /= 2;
    }
    return res;
}

// 計算模逆元
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, a1, m, k;
    if (!(cin >> n >> a1 >> m >> k)) return 0;

    // 使用 vector 儲存生成的序列 a 與前綴乘積 prefix_prod
    // 為了節省記憶體，我們其實不需要儲存完整的 a 序列兩次，但為了邏輯清晰先開兩個 vector
    // n 最大 10^7，long long 佔 8 bytes，兩個 vector 約 160MB，在一般限制內 (通常 256MB~512MB)
    // 若記憶體限制極嚴苛，可優化為只存 prefix_prod，並在第二輪重新生成 a_i，但這裡假設標準限制
    
    vector<long long> a(n);
    vector<long long> prefix_prod(n);

    // 1. 生成序列並計算前綴乘積
    // 注意題目公式：a_i = max(1, (m * a_{i-1} + k) % MOD) for i > 1 (0-indexed: i > 0)
    
    long long current_val = a1;
    // 處理第一個元素
    // 題目保證 a1 >= 1，但若 a1 % MOD == 0? 題目說 a1 < MOD 且為正整數，所以 a1 != 0
    a[0] = current_val;
    prefix_prod[0] = current_val;

    for (int i = 1; i < n; ++i) {
        // 計算下一個值
        // 使用 __int128 防止乘法溢出
        long long next_val = (long long)((__int128)m * current_val + k) % MOD;
        if (next_val < 1) next_val = 1; // max(1, ...)
        
        current_val = next_val;
        a[i] = current_val;
        
        // 更新前綴乘積
        prefix_prod[i] = (__int128)prefix_prod[i-1] * current_val % MOD;
    }

    // 2. 計算總乘積的模逆元
    // total_inv = (a_0 * a_1 * ... * a_{n-1})^-1
    long long total_inv = modInverse(prefix_prod[n-1]);

    // 3. 反向遞推計算每個元素的模逆元並同時計算 XOR 和
    // 原理：
    // inv_prefix[i] = (a_0 * ... * a_i)^-1
    // inv_prefix[i-1] = inv_prefix[i] * a_i
    // a_i^-1 = inv_prefix[i] * prefix_prod[i-1] (若 i>0)
    // 或者更直接地：
    // 我們知道 suffix_inv[i] = (a_i * ... * a_{n-1})^-1
    // 但我們用前綴乘積的反向推导：
    // 令 P[i] = a_0 * ... * a_i
    // P[n-1]^-1 已知。
    // P[i-1]^-1 = P[i]^-1 * a_i
    // a_i^-1 = P[i]^-1 * P[i-1]
    
    long long xor_sum = 0;
    long long current_inv_suffix = total_inv; // 這代表 (a_i * a_{i+1} * ... * a_{n-1})^-1 ? 不完全是
    
    // 讓我們重新整理邏輯以符合單遍反向掃描：
    // 我們想要 calc inv(a_i) for all i.
    // 我們有 P[i] = a_0 * ... * a_i.
    // 我們有 TotalInv = P[n-1]^-1.
    // 定義 SuffixInv[i] = (a_i * a_{i+1} * ... * a_{n-1})^-1.
    // 則 SuffixInv[n-1] = a_{n-1}^-1 = TotalInv * P[n-2].
    // 一般化：a_i^-1 = (P[i] * (P[i-1])^-1 * ... )? 
    // 最簡單的方法：
    // 維護一個變數 running_inv，初始為 TotalInv (即 P[n-1]^-1).
    // 從 i = n-1  downto 0:
    //   此時 running_inv = (a_0 * ... * a_i)^-1 ? 不對。
    
    // 正確的反向遞推邏輯：
    // 令 inv_P[i] 為前綴乘積 P[i] 的逆元。
    // inv_P[n-1] = total_inv.
    // inv_P[i-1] = inv_P[i] * a[i] % MOD.
    // 那麼 a[i] 的逆元 = inv_P[i] * P[i-1] % MOD (當 i > 0).
    // 當 i = 0, a[0] 的逆元 = inv_P[0].
    
    // 為了節省空間，我們不需要儲存 inv_P 陣列，只需一個變數當前前綴逆元。
    // 但我們需要 P[i-1] 的值。我們可以即時重新生成 a[i] 或者重用 a[] 陣列。
    // 既然我們已經有 a[] 和 prefix_prod[]，我們可以直接用。
    
    // 步驟：
    // 1. 計算 inv_P[n-1]
    // 2. 從 n-1 迴圈到 0:
    //    如果 i == n-1: current_inv_P = total_inv
    //    否則: current_inv_P = (current_inv_P * a[i+1]) % MOD  <-- 這是錯的，方向反了
    
    // 重來：
    // inv_P[i] = (P[i])^-1
    // P[i] = P[i-1] * a[i]  => P[i-1] = P[i] * a[i]^-1 (這需要逆元，沒幫助)
    // 關係是：inv_P[i-1] = inv_P[i] * a[i]
    // 證明：inv_P[i] * a[i] = (P[i-1]*a[i])^-1 * a[i] = P[i-1]^-1 * a[i]^-1 * a[i] = P[i-1]^-1
    
    // 所以演算法：
    // current_inv_P = total_inv (這是 P[n-1]^-1)
    // 從 i = n-1 下修到 0:
    //   若 i == 0:
    //     inv_a_0 = current_inv_P
    //   若 i > 0:
    //     inv_a_i = current_inv_P * prefix_prod[i-1] % MOD
    //   
    //   更新 current_inv_P 給下一次迭代 (變成 P[i-1]^-1):
    //   current_inv_P = current_inv_P * a[i] % MOD
    
    long long current_inv_P = total_inv;
    
    // 我們需要從後往前算，但 XOR 運算順序無關緊要，所以可以直接累加
    for (int i = n - 1; i >= 0; --i) {
        long long inv_ai;
        if (i == 0) {
            inv_ai = current_inv_P;
        } else {
            inv_ai = (__int128)current_inv_P * prefix_prod[i-1] % MOD;
        }
        
        xor_sum ^= inv_ai;
        
        // 更新 current_inv_P 成為 P[i-1]^-1
        // P[i-1]^-1 = P[i]^-1 * a[i]
        current_inv_P = (__int128)current_inv_P * a[i] % MOD;
    }

    cout << xor_sum << "\n";

    return 0;
}
