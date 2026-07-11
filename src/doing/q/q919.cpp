#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

long long dp[11][10][1024][10];
int K;
int memo_visited[11][10][1024][10];
int visit_token = 0;

// 計算數字各位數之和模 9 的值 (用於快速檢查整除性，但這裡主要用餘數)
// 實際上我們直接維護 mod K 的餘數

long long solve(int pos, int current_mod, int mask, int leading_zeros, bool is_first_call) {
    if (pos == 0) {
        // 所有位數都填完了
        // 檢查是否為迴文：mask 中每個數字出現次數必須是偶數，或者恰好有一個數字出現奇數次
        int odd_count = 0;
        for (int i = 0; i <= 9; ++i) {
            int count = (mask >> (i * 2)) & 3; // 取出該數字出現次數 (0-3, 但實際可能更多，需重新設計 mask)
            // 上面的 mask 設計有問題，因為 n 可達 10，每個數字最多出現 10 次，2 bits 不夠
            // 我們需要重新設計狀態或改用其他方式
        }
        return (current_mod == 0) ? 1 : 0;
    }
    return 0;
}

// 由於上述 DP 狀態設計有困難（mask 記錄計數太複雜），我們換個思路：
// n 很小 (<=10)，我們可以枚舉所有可能的數字組合（多重集），然後對每個組合：
// 1. 計算能組成多少個不同的迴文數
// 2. 檢查這些迴文數是否能被 k 整除
// 但這樣也很複雜，因為要檢查整除性需要知道具體排列。

// 更好的方法：直接 DFS 生成所有 n 位數的迴文，然後檢查是否能由某個排列得到且能被 k 整除？
// 不，題目是：給定 n 位數，可以任意重排，問有多少個 n 位數（原始數字）滿足：存在一種重排方式是迴文且能被 k 整除。
// 等價於：有多少個多重集（n 個數字，首位不能全為 0 的特殊處理），使得：
//   (a) 該多重集能組成至少一個迴文（即：奇數長則恰一數字出現奇數次；偶數長則所有數字出現偶數次）
//   (b) 該多重集能組成至少一個能被 k 整除的迴文數。

// 注意：條件 (b) 不等於「該多重集組成的某個數能被 k 整除」，而是「該多重集組成的某個迴文數能被 k 整除」。
// 所以我們應該：枚舉所有可能的迴文數（n 位數），檢查它是否能被 k 整除，然後計算這個迴文數對應的多重集能代表多少個不同的原始數字（即排列數，扣除前導零的情況）。

// 步驟：
// 1. 生成所有 n 位數的迴文數（通過生成前半部分）
// 2. 對每個迴文數，檢查是否 % k == 0
// 3. 如果是，計算這個迴文數的數字多重集能組成多少個有效的 n 位數（即：總排列數 - 以 0 開頭的排列數）
// 4. 累加答案

// 如何生成 n 位數的迴文？
// 若 n 為偶數：生成前 n/2 位，後 n/2 位鏡像
// 若 n 為奇數：生成前 (n+1)/2 位，後 (n-1)/2 位鏡像（中間位不鏡像）

// 注意：第一位不能是 0

long long factorial[11];
void precompute_factorial() {
    factorial[0] = 1;
    for (int i = 1; i <= 10; ++i) factorial[i] = factorial[i-1] * i;
}

long long count_permutations(const vector<int>& count, int total_digits) {
    long long res = factorial[total_digits];
    for (int i = 0; i <= 9; ++i) {
        if (count[i] > 1) {
            res /= factorial[count[i]];
        }
    }
    return res;
}

long long count_permutations_with_leading_zero(const vector<int>& count, int total_digits) {
    if (count[0] == 0) return 0;
    vector<int> new_count = count;
    new_count[0]--;
    return count_permutations(new_count, total_digits - 1);
}

int main() {
    precompute_factorial();
    int n;
    while (cin >> n >> K) {
        long long ans = 0;
        
        int half_len = (n + 1) / 2;
        // 枚舉前半部分（包含中間位，如果 n 是奇數）
        // 範圍：從 10^(half_len-1) 到 10^half_len - 1
        int start = 1;
        for (int i = 1; i < half_len; ++i) start *= 10;
        int end = start * 10 - 1;
        
        for (int num = start; num <= end; ++num) {
            string s = to_string(num);
            string full_palindrome = s;
            // 構建後半部分
            if (n % 2 == 1) {
                // 奇數長度，最後一位是中間位，不重複
                for (int i = (int)s.size() - 2; i >= 0; --i) {
                    full_palindrome += s[i];
                }
            } else {
                for (int i = (int)s.size() - 1; i >= 0; --i) {
                    full_palindrome += s[i];
                }
            }
            
            // 轉換為數字並檢查整除性
            long long pal_val = stoll(full_palindrome);
            if (pal_val % K != 0) continue;
            
            // 統計數字出現次數
            vector<int> cnt(10, 0);
            for (char c : full_palindrome) {
                cnt[c - '0']++;
            }
            
            // 計算這個多重集能組成多少個有效的 n 位數
            long long total = count_permutations(cnt, n);
            long long with_leading_zero = count_permutations_with_leading_zero(cnt, n);
            ans += (total - with_leading_zero);
        }
        
        cout << ans << endl;
    }
    return 0;
}
