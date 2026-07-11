#include <iostream>
#include <vector>

using namespace std;

// 計算 (a * b) % m，避免 overflow
long long mul_mod(long long a, long long b, long long m) {
    return (a * b) % m;
}

// 快速冪取模：計算 (base^exp) % mod
int power(int base, long long exp, int mod) {
    long long result = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * b) % mod;
        }
        b = (b * b) % mod;
        exp >>= 1;
    }
    return static_cast<int>(result);
}

// 計算 n! 中質因子 p 的個數
long long count_factor(int n, int p) {
    long long count = 0;
    long long pp = p;
    while (pp <= n) {
        count += n / pp;
        if (n / p < pp) break; // 避免 overflow
        pp *= p;
    }
    return count;
}

// 計算 1..n 中移除所有因子 2 和 5 後的乘積 mod 10
// 使用递归方法計算 D(n) = (product of i in [1, n] where gcd(i, 10)=1) mod 10
// 利用週期性：1, 3, 7, 9 的乘積 mod 10 = 9
// f(n) = f(n/5) * g(n) * 2^(n/5) ? 不，這是包含 2 的情況。
// 我們需要的是移除 2 和 5 後的純奇數部分乘積 mod 10? 
// 不完全是，我們要計算的是 n! / (10^k) mod 10.
// 公式: L(n) = (L(n/5) * P(n) * 2^(n/5)) % 10
// 其中 P(n) 是 1..n 中不能被 5 整除的數，移除因子 2 後的乘積 mod 10?
// 讓我們用更標準的遞迴公式：
// D(n) = last non-zero digit of n!
// D(n) = D(n/5) * D_single(n) * 2^(n/5) mod 10
// D_single(n) = product of {i | 1<=i<=n, i%5!=0} 去除因子 2 後 mod 10? 
// 其實有一個更簡單的遞迴關係專門處理 mod 10:
// 令 f(n) 為 n! 去掉所有因子 2 和 5 後的末位數字。
// 但我們需要保留多餘的 2 (因為 2 的數量通常多於 5)。
// 正確的高效遞迴公式 (mod 10):
// ans(n) = ans(n/5) * table[n%10] * pow(2, n/5, 10) % 10
// 這個公式假設我們已經處理了 5 的倍數，並將它們轉化為 n/5 的子問題。
// 對於非 5 倍數的部分，它們的末位數字呈現週期性。
// 1*2*3*4*6*7*8*9... mod 10 (忽略 5 的倍數，並暫時忽略 2 的因子影響？)
// 讓我們重新推導一個穩健的 O(log n) 解法。

// 目標：計算 n! / 10^k mod 10, 其中 k 是 10 的冪次。
// n! = 2^a * 5^b * other_primes
// k = min(a, b) = b (因為 a >= b)
// 結果 = 2^(a-b) * other_primes mod 10

// 我們可以分別計算：
// 1. extra_twos = a - b
// 2. product_without_2_or_5 = (n! / (2^a * 5^b)) mod 10
// 最後結果 = (product_without_2_or_5 * 2^(extra_twos)) % 10

// 計算 product_without_2_or_5 mod 10:
// 定義 G(n) = product of {i | 1<=i<=n, gcd(i, 10)=1} mod 10
// 實際上我們要移除所有 2 和 5。
// 令 F(n) 為 1..n 中所有數移除因子 2 和 5 後的乘積 mod 10。
// F(n) = F(n/2) * F_odd(n) ? 不太對。
// 使用 Legendre 公式的變體或遞迴。
// 考慮數字 1, 2, ..., n.
// 移除所有 5 的倍數：剩下來的數每 10 個一組，其移除 2,5 後的乘積 mod 10 是固定的嗎？
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
// 移除 5, 10 -> 1, 2, 3, 4, 6, 7, 8, 9
// 移除因子 2:
// 1 -> 1
// 2 -> 1
// 3 -> 3
// 4 -> 1
// 6 -> 3
// 7 -> 7
// 8 -> 1
// 9 -> 9
// 乘積: 1*1*3*1*3*7*1*9 = 81 -> 1.
// 似乎每 10 個數的貢獻是 1? 
// 讓我們檢查 1..10 移除 2,5 後的乘積:
// 1, 1, 3, 1, (skip 5), 3, 7, 1, 9, (skip 10->1)
// 1*1*3*1*3*7*1*9*1 = 567 -> 7? 
// 等等，4 移除 2 兩次變成 1. 6 移除 2 變成 3. 8 移除 2 三次變成 1.
// 1, 1, 3, 1, 3, 7, 1, 9. 
// 1*1=1, *3=3, *1=3, *3=9, *7=63->3, *1=3, *9=27->7.
// 所以 1..10 的貢獻是 7.
// 但是 11..20 呢？
// 11(1), 12(3), 13(3), 14(7), 15(skip), 16(1), 17(7), 18(9), 19(9), 20(skip)
// 這裡的數字 mod 10 與 1..10 相同，但移除因子 2 後的值可能不同嗎？
// 12 = 4*3 -> 3. 2 = 2*1 -> 1. 不同。
// 所以不能簡單地用週期。

// 改用標準遞迴公式：
// 設 D(n) 為 n! 的最後一位非零數字。
// D(n) = D(n/5) * D(n%10) * 2^(n/5) % 10 ? 
// 這個公式在某些情況下有效，但需要精確定義 D(n%10) 的表。
// 參考文獻指出：
// Last non-zero digit of n! can be computed by:
// f(n) = f(n/5) * g(n) % 10
// where g(n) = product of digits of numbers from 1 to n excluding multiples of 5, removing factors of 2 appropriately?
// 更簡單的公式：
// L(n) = (L(n/5) * T[n%10] * 2^(n/5)) % 10
// 其中 T = {1, 1, 2, 6, 4, 4, 4, 8, 4, 6} (這是 n! mod 10 for n<10 ignoring 5s? No)
// 讓我們查證這個表 T。
// n=1: 1
// n=2: 2
// n=3: 6
// n=4: 24 -> 4
// n=5: skip (handled by recursion)
// n=6: 6*1=6? No, 6! = 720 -> 2. 
// 這個公式通常是：
// D(n) = D(n/5) * D(n%5) * 2^(n/5) % 10? 
// 讓我們手動驗證小數字。
// D(1)=1
// D(2)=2
// D(3)=6
// D(4)=4
// D(5)=D(1)*D(0)*2^1 = 1*1*2=2. (5!=120 -> 2). Correct.
// D(6)=D(1)*D(1)*2^1 = 1*1*2=2. (6!=720 -> 2). Correct.
// D(7)=D(1)*D(2)*2^1 = 1*2*2=4. (7!=5040 -> 4). Correct.
// D(8)=D(1)*D(3)*2^1 = 1*6*2=12->2. (8!=40320 -> 2). Correct.
// D(9)=D(1)*D(4)*2^1 = 1*4*2=8. (9!=362880 -> 8). Correct.
// D(10)=D(2)*D(0)*2^2 = 2*1*4=8. (10!=3628800 -> 8). Correct.
// D(11)=D(2)*D(1)*2^2 = 2*1*4=8. (11! ... 8). Correct.
// D(12)=D(2)*D(2)*2^2 = 2*2*4=16->6. (12! ... 6). Correct.
// D(13)=D(2)*D(3)*2^2 = 2*6*4=48->8. (13! ... 8). Correct.
// D(14)=D(2)*D(4)*2^2 = 2*4*4=32->2. (14! ... 2). Correct.
// D(15)=D(3)*D(0)*2^3 = 6*1*8=48->8. (15! ... 8). Correct.
// 看起來公式 D(n) = D(n/5) * D(n%5) * 2^(n/5) % 10 是正確的，只要我們定義好 D(0)..D(4)。
// D(0) = 1
// D(1) = 1
// D(2) = 2
// D(3) = 6
// D(4) = 4
// 注意：這裡的 D(n%5) 其實是 (n%5)! 的最後一位非零數字，因為 n%5 < 5，沒有因子 5。
// 所以表是: [1, 1, 2, 6, 4]
// 並且我们需要快速冪計算 2^(n/5) % 10。
// 2 的冪次 mod 10 的週期是 4: 2, 4, 8, 6, 2...
// 指數很大時，可以用 (exp-1)%4 + 1 來簡化？或者直接快速冪。
// 由於 mod 10 很小，快速冪很快。

int get_last_non_zero_digit(long long n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    
    // Base cases for n < 5
    // 0! = 1 -> 1
    // 1! = 1 -> 1
    // 2! = 2 -> 2
    // 3! = 6 -> 6
    // 4! = 24 -> 4
    static const int table[] = {1, 1, 2, 6, 4};
    
    if (n < 5) return table[n];
    
    long long q = n / 5;
    int r = n % 5;
    
    int sub = get_last_non_zero_digit(q);
    int rem = table[r];
    int pow2 = power(2, q, 10);
    
    int res = sub * rem % 10;
    res = res * pow2 % 10;
    
    return res;
}

int main() {
    // 優化 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n) {
        cout << get_last_non_zero_digit(n) << "\n";
    }
    
    return 0;
}
