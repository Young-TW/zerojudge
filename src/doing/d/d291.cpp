#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 計算 (a * b) % mod，避免溢出
long long mul_mod(long long a, long long b, long long mod) {
    return (a * b) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        if (n == 0) continue; // 雖然題目說 0 < n，但防呆一下

        long long mod = 1;
        for (int i = 0; i < n; ++i) {
            mod *= 10;
        }

        // 我們要找 x 使得 x^2 ≡ x (mod 10^n)
        // 即 x(x-1) ≡ 0 (mod 10^n)
        // 因為 10^n = 2^n * 5^n，且 gcd(x, x-1) = 1
        // 所以有兩種情況：
        // 1. x ≡ 0 (mod 2^n) 且 x ≡ 1 (mod 5^n) -> 對應到結尾是 ...625 的那個 (例如 625, 0625)
        // 2. x ≡ 1 (mod 2^n) 且 x ≡ 0 (mod 5^n) -> 對應到結尾是 ...376 的那個 (例如 376, 9376)
        // 注意：題目排除 0 和 1，所以我們只找這兩個非平凡解。

        // 使用 Hensel's Lemma 或直接遞推構造
        // 假設我們已經知道 x_k 滿足 x_k^2 ≡ x_k (mod 10^k)
        // 我們想找 x_{k+1} = x_k + d * 10^k，其中 d ∈ [0, 9]
        // 使得 x_{k+1}^2 ≡ x_{k+1} (mod 10^{k+1})
        
        // 展開：(x_k + d * 10^k)^2 ≡ x_k + d * 10^k (mod 10^{k+1})
        // x_k^2 + 2 * x_k * d * 10^k + d^2 * 10^{2k} ≡ x_k + d * 10^k (mod 10^{k+1})
        // 因為 k >= 1, 2k >= k+1 (當 k>=1)，所以 d^2 * 10^{2k} ≡ 0 (mod 10^{k+1})
        // 得到：x_k^2 + 2 * x_k * d * 10^k ≡ x_k + d * 10^k (mod 10^{k+1})
        // 移項：(x_k^2 - x_k) + (2 * x_k - 1) * d * 10^k ≡ 0 (mod 10^{k+1})
        // 令 x_k^2 - x_k = A * 10^k (因為 x_k 是解 mod 10^k，所以差一定是 10^k 的倍數)
        // 則 A * 10^k + (2 * x_k - 1) * d * 10^k ≡ 0 (mod 10^{k+1})
        // 兩邊除以 10^k：A + (2 * x_k - 1) * d ≡ 0 (mod 10)
        // 所以 d ≡ -A * (2 * x_k - 1)^{-1} (mod 10)
        
        // 但更簡單的方法是直接枚舉 d (0~9)，因為只有 10 種可能。
        
        // 初始值 (n=1)
        // 解為 5 和 6
        long long x1 = 5;
        long long x2 = 6;
        
        long long current_mod = 10;
        
        for (int k = 1; k < n; ++k) {
            // 從 10^k 擴展到 10^{k+1}
            long long next_mod = current_mod * 10;
            
            // 擴展 x1
            long long diff1 = (mul_mod(x1, x1, next_mod) - x1 + next_mod) % next_mod;
            // diff1 應該是 current_mod 的倍數
            long long A1 = diff1 / current_mod;
            long long d1 = -1;
            for (int d = 0; d <= 9; ++d) {
                if ((A1 + (2 * x1 - 1) * d) % 10 == 0) {
                    d1 = d;
                    break;
                }
            }
            x1 = x1 + d1 * current_mod;
            
            // 擴展 x2
            long long diff2 = (mul_mod(x2, x2, next_mod) - x2 + next_mod) % next_mod;
            long long A2 = diff2 / current_mod;
            long long d2 = -1;
            for (int d = 0; d <= 9; ++d) {
                if ((A2 + (2 * x2 - 1) * d) % 10 == 0) {
                    d2 = d;
                    break;
                }
            }
            x2 = x2 + d2 * current_mod;
            
            current_mod = next_mod;
        }
        
        // 確保結果在 [0, mod-1] 範圍內，雖然上述算法應該自然滿足
        x1 %= mod;
        x2 %= mod;
        
        // 轉換為字串並補零
        string s1 = to_string(x1);
        string s2 = to_string(x2);
        
        while (s1.length() < n) s1 = "0" + s1;
        while (s2.length() < n) s2 = "0" + s2;
        
        // 輸出較小的在前
        if (s1 < s2) {
            cout << s1 << "\n" << s2 << "\n";
        } else {
            cout << s2 << "\n" << s1 << "\n";
        }
    }

    return 0;
}
