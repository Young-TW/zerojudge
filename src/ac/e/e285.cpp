#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 大數乘法 (大數 * int)
string multiply(const string& num, int k) {
    string result = "";
    int carry = 0;
    for (int i = num.size() - 1; i >= 0; --i) {
        int digit = num[i] - '0';
        long long prod = (long long)digit * k + carry;
        result.push_back((prod % 10) + '0');
        carry = prod / 10;
    }
    while (carry) {
        result.push_back((carry % 10) + '0');
        carry /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

// 比較大數與 int 的 n 次方
// 返回 -1: k^n < p, 0: k^n == p, 1: k^n > p
int compare_power(int k, int n, const string& p_str) {
    if (k == 1) {
        if (p_str == "1") return 0;
        return -1; // 1^n = 1 < p (since p >= 1 and if p!=1 then p>1)
    }
    
    string current = "1";
    // 快速冪概念，但這裡直接乘 n 次可能太慢，改用二分法或估算位數
    // 由於 k <= 2^32, n <= 100000, 直接乘會超時。
    // 我們改用對數估算或二分搜尋搭配大數運算。
    // 但題目保證 k 是整數且範圍在 unsigned int 內。
    // 實際上，因為 p 可以非常大 (10^100000)，我們不能用 double 直接算。
    // 但是 k 的範圍很小 (<= 4294967295)，我們可以對 k 進行二分搜尋。
    
    // 優化：先估算 k 的位數或使用 log10
    // log10(k^n) = n * log10(k) = log10(p)
    // log10(k) = log10(p) / n
    // k = 10^(log10(p)/n)
    
    // 計算 p 的 log10 近似值
    // p_str 長度為 L, 則 log10(p) ≈ (L-1) + log10(first_few_digits)
    int len = p_str.length();
    double log_p = len - 1;
    if (len > 0) {
        string prefix = p_str.substr(0, min(len, 18));
        double first_part = stod(prefix);
        log_p += log10(first_part) - (prefix.length() - 1);
    }
    
    double log_k = log_p / n;
    double est_k = pow(10.0, log_k);
    
    long long low = max(1LL, (long long)(est_k * 0.9));
    long long high = min((long long)4294967295LL, (long long)(est_k * 1.1));
    
    // 確保範圍涵蓋正確答案
    if (low > high) swap(low, high);
    if (low < 1) low = 1;
    if (high > 4294967295LL) high = 4294967295LL;

    // 在 [low, high] 範圍內二分搜尋或用 pow 檢查
    // 由於範圍很小，可以直接遍歷或二分
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        
        // 計算 mid^n 並與 p 比較
        // 為了避免完全計算大數，可以先比較位數
        double log_val = n * log10((double)mid);
        if (log_val < log_p - 1e-9) {
            low = mid + 1;
            continue;
        } else if (log_val > log_p + 1e-9) {
            high = mid - 1;
            continue;
        }
        
        // 如果 log 很接近，才進行精確的大數計算
        string calc = "1";
        bool overflow = false;
        // 使用快速冪計算 mid^n
        long long base = mid;
        int exp = n;
        vector<string> powers;
        powers.push_back(to_string(base));
        
        // 預先計算 base^(2^i) 直到超過 n
        // 但這樣可能太複雜，直接簡單乘？不，n 可達 100000
        // 必須用快速冪
        string res = "1";
        string b = to_string(mid);
        int e = n;
        
        while (e > 0) {
            if (e % 2 == 1) {
                res = multiply(res, stoi(b)); // 這裡有問題，b 可能很大嗎？不，b 是 mid 的字串，mid 是 long long
                // 等等，multiply 函數是 string * int
                // 但 res 可能已經很大了，不能轉成 int
                // 需要一個 string * string 的函數？
                // 不，題目說 k 是 int 範圍，但中間結果會很大。
                // 我的 multiply 函數只支援 string * int。
                // 快速冪需要 string * string 嗎？
                // 其實不需要，因為底數始终是 k (int)，我們只是要算 k^n。
                // 但快速冪過程中會出現 k^2, k^4 等，這些會超過 int。
                // 所以我们需要 string * string。
            }
            e /= 2;
            if (e > 0) {
                // b = b * b (string * string)
                // 這太複雜了。
            }
        }
        
        // 重新思考：既然 k 很小，我們可以直接用二分法找 k，然後驗證 k^n == p
        // 驗證時，如果 n 很大，k^n 會巨大無比。
        // 但我們可以用對數先篩選，只有非常接近時才做精確計算。
        // 或者，既然題目保證有整數解，且 log 估算通常很準，
        // 我們可以直接四捨五入 est_k 然後驗證。
        
        long long candidate = round(est_k);
        if (candidate < 1) candidate = 1;
        if (candidate > 4294967295LL) candidate = 4294967295LL;
        
        // 驗證 candidate
        // 如何驗證？計算 candidate^n 看是否等於 p_str
        // 如果 n 很大，計算量很大。
        // 但題目說單一測資檔不超過 20000 組，且總大小 35MB。
        // 這意味著平均 p 的長度不會太長，或者 n 大的時候 p 的長度也不會極端長？
        // 不，p 可以到 10^100000。
        // 如果 n=100000, k=2, 則 p 約 30000 位數。
        // 如果 n=1, p 可以是 10^100000。
        // 如果 n 很大，k 必須很小。
        // 如果 k=1, p=1。
        // 如果 k>=2, n<=100000, 則 p 的位數 <= 100000 * log10(4*10^9) ≈ 100000 * 9.6 ≈ 960000 位。
        // 題目說 p <= 10^100000，所以位數最多 100001 位。
        // 這表示 n * log10(k) <= 100000。
        // 所以如果 n 很大，k 必須很小。
        // 例如 n=100000, k 最多是 10 (10^100000)。
        // 所以計算 k^n 的複雜度取決於結果的位數，最多 100000 位。
        // 用快速冪 + 大數乘法 (FFT? 不，太複雜) 
        // 簡單的 O(D^2) 乘法，D=100000，太慢。
        // 但注意，底數 k 很小 (如果是大 n)，或者 n 很小 (如果是大 k)。
        // 情況 1: k 小 (<= 1000), n 大。此時可以用重複平方，但乘法是 string * int (因為底數小？不，中間結果大)。
        // 情況 2: k 大，n 小 (<= 10)。此時可以直接乘。
        
        // 讓我們根據 n 的大小選擇策略。
        // 如果 n 很小 (例如 <= 60)，直接用 double pow 然後驗證？不，精度不夠。
        // 如果 n 很小，直接做整數快速冪 (用 string 存結果)。
        // 如果 n 很大，則 k 一定很小。
        // 如果 k=1, ans=1。
        // 如果 k=2, n 可達 332192 (2^332192 ~ 10^100000)。
        // 我們需要一個高效的 power 函數。
        
        // 其實，既然我們已經用 log 估算出 candidate，而且題目保證有整數解。
        // 我們只需要驗證 candidate 是否正確。
        // 驗證方法：計算 candidate^n，看是否等於 p。
        // 為了加速，我們可以模一個大質數？不行，可能有碰撞。
        // 但我們可以模多個大質數來增加信心。
        // 或者，既然題目保證有解，且 log 估算對於整數來說非常精確（除非數字極大且相鄰整數的 log 差異小於 double 精度）。
        // double 有 53 bits 有效數字，約 15-17 位十進制。
        // 如果 k 和 k+1 的 log 差異小於 1e-15，可能會出錯。
        // n * (log(k+1) - log(k)) = n * log(1 + 1/k) ≈ n/k.
        // 如果 n/k < 1e-15，則可能分不清。
        // 最大 n=100000, 最小 k=1 -> n/k = 100000 (安全)
        // 最大 k=4e9, 最小 n=1 -> n/k = 2.5e-10 (安全)
        // 最壞情況：n 大，k 大？不可能，因為 p = k^n <= 10^100000。
        // 如果 k=4e9, n 最多是 log(10^100000)/log(4e9) ≈ 100000/9.6 ≈ 10416。
        // 此時 n/k ≈ 10416 / 4e9 ≈ 2.6e-6 (遠大於 1e-15)。
        // 所以 double 精度足夠區分相鄰整數的 n 次方根。
        // 因此，round(est_k) 一定是正確答案。
        // 我們甚至不需要驗證！
        
        cout << candidate << endl;
        return 0; // 結束這個測資
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    string p_str;
    while (cin >> n >> p_str) {
        if (p_str == "1") {
            cout << 1 << "\n";
            continue;
        }
        int len = p_str.length();
        double log_p = len - 1;
        if (len > 0) {
            string prefix = p_str.substr(0, min(len, 18));
            double first_part = stod(prefix);
            log_p += log10(first_part) - (prefix.length() - 1);
        }
        double log_k = log_p / n;
        double est_k = pow(10.0, log_k);
        long long candidate = round(est_k);
        if (candidate < 1) candidate = 1;
        if (candidate > 4294967295LL) candidate = 4294967295LL;
        cout << candidate << "\n";
    }
    return 0;
}
