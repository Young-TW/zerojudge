#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

// 大數減法 (a = a - b)，假設 a >= b
void bigSub(string &a, const string &b) {
    int n = a.size(), m = b.size();
    int carry = 0;
    for (int i = 0; i < n; ++i) {
        int digitA = a[n - 1 - i] - '0';
        int digitB = (i < m) ? b[m - 1 - i] - '0' : 0;
        int sub = digitA - digitB - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        a[n - 1 - i] = sub + '0';
    }
    // 移除前導零
    size_t firstNonZero = a.find_first_not_of('0');
    if (firstNonZero == string::npos) {
        a = "0";
    } else {
        a = a.substr(firstNonZero);
    }
}

// 大數除法 (a / b)，回傳商與餘數 (pair<string, string>)
// 假設 b 是普通整數且 b > 0
pair<string, string> bigDivMod(const string &a, long long b) {
    string quotient;
    quotient.reserve(a.size());
    long long remainder = 0;
    
    for (char c : a) {
        remainder = remainder * 10 + (c - '0');
        long long q = remainder / b;
        remainder %= b;
        quotient.push_back(q + '0');
    }
    
    size_t firstNonZero = quotient.find_first_not_of('0');
    if (firstNonZero == string::npos) {
        quotient = "0";
    } else {
        quotient = quotient.substr(firstNonZero);
    }
    
    return {quotient, to_string(remainder)};
}

// 判斷大數是否為偶數
bool isEven(const string &n) {
    return (n.back() - '0') % 2 == 0;
}

// 判斷大數是否小於等於長整數
bool isLessOrEqualLong(const string &n, long long val) {
    if (n.size() > 18) return false;
    long long num = stoll(n);
    return num <= val;
}

// Miller-Rabin 測試的模冪運算 (base^exp % mod)，支援大數 base
long long modPowBigBase(string base, long long exp, long long mod) {
    // 先將 base 對 mod 取模
    string temp = base;
    while (temp.size() > 18 || stoll(temp) >= mod) {
        auto res = bigDivMod(temp, mod);
        temp = res.first;
        if (res.second == "0") break;
        // 如果商是 0，則餘數就是結果
        if (temp == "0") {
            temp = res.second;
            break;
        }
        // 這裡需要更精確的處理，直接用餘數
        temp = res.second;
        if (temp == "0") return 0;
        if (stoll(temp) < mod) break;
    }
    long long b = stoll(temp) % mod;
    
    long long result = 1;
    b %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (__int128)result * b % mod;
        }
        b = (__int128)b * b % mod;
        exp /= 2;
    }
    return result;
}

// Miller-Rabin 素性測試
bool millerRabin(const string &n, int k = 5) {
    if (n == "2" || n == "3") return true;
    if (n.size() == 1 && stoll(n) < 2) return false;
    if (isEven(n)) return false;
    
    // n-1 = d * 2^r
    string d = n;
    bigSub(d, "1");
    int r = 0;
    while (isEven(d)) {
        bigSub(d, "0"); // 暫時借用來除以 2? 不行，要實作除以 2
        // 簡單做法：直接檢查最後一位，然後模擬除以 2
        // 這裡為了簡化，我們用另一種方式計算 r 和 d
        r++;
        // 重新計算 d = (n-1) / 2^r
        d = n;
        bigSub(d, "1");
        for(int i=0; i<r; ++i) {
            // 除以 2
            string tempD;
            tempD.reserve(d.size());
            int carry = 0;
            for (char c : d) {
                int digit = (c - '0') + carry * 10;
                int q = digit / 2;
                carry = digit % 2;
                if (!(tempD.empty() && q == 0)) {
                    tempD.push_back(q + '0');
                }
            }
            if (tempD.empty()) tempD = "0";
            d = tempD;
        }
    }
    
    // 使用固定的幾個 base 進行測試，對於 10^100 以上的數，這些 base 足夠
    vector<long long> bases;
    if (isLessOrEqualLong(n, 2047)) bases = {2};
    else if (isLessOrEqualLong(n, 1373653)) bases = {2, 3};
    else if (isLessOrEqualLong(n, 9080191)) bases = {31, 73};
    else if (isLessOrEqualLong(n, 25326001)) bases = {2, 3, 5};
    else if (isLessOrEqualLong(n, 3215031751LL)) bases = {2, 3, 5, 7};
    else if (isLessOrEqualLong(n, 4759123141LL)) bases = {2, 7, 61};
    else if (isLessOrEqualLong(n, 1122004669633LL)) bases = {2, 13, 23, 1662803};
    else if (isLessOrEqualLong(n, 2152302898747LL)) bases = {2, 3, 5, 7, 11};
    else if (isLessOrEqualLong(n, 3474749660383LL)) bases = {2, 3, 5, 7, 11, 13};
    else if (isLessOrEqualLong(n, 341550071728321LL)) bases = {2, 3, 5, 7, 11, 13, 17};
    else if (isLessOrEqualLong(n, 3825123056546413051LL)) bases = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    else {
        // 對於非常大的數，使用前幾個質數作為 base
        bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    }
    
    for (long long a : bases) {
        if (isLessOrEqualLong(n, a)) break;
        long long x = modPowBigBase(n, a, stoll(n)); // 這裡有問題，stoll(n) 會 overflow
        // 修正：我們需要一個能處理大數 mod 的函數，但 Miller-Rabin 的 base a 是小數
        // 問題在於 modPowBigBase 的第三個參數 mod 是大數，這在標準 C++ 無法直接處理
        // 這題的關鍵在於 p 是大質數，但我們只需要驗證它是不是質數嗎？
        // 題目說輸入是質數 p，所以我們不需要驗證！
        // 我們只需要計算 sum(1/q) for q <= p
        // 但 p 大到 10^92300，我們不可能列舉所有質數
        // 這題一定有數學技巧
        
        // 重新思考：題目給的是質數 p，要求 sum(1/q) for all prime q <= p
        // 根據質數定理，sum(1/q) ~ ln(ln(p)) + M (M 是 Meissel-Mertens constant ≈ 0.261497)
        // 對於 p > 10^100，這個近似非常準確
        // 所以我們不需要真的列舉質數，只需要用這個公式
        
        // 因此，這題不需要 Miller-Rabin，也不需要大數運算來列舉質數
        // 只需要計算 ln(ln(p)) + M
        
        // 但我們需要處理大數 p 的自然對數
        // ln(p) = ln(m * 10^e) = ln(m) + e * ln(10)
        // 其中 p = m * 10^e, 1 <= m < 10
        
        // 讓我們重寫整個解決方案
        return true; // 佔位符，實際邏輯在下面
    }
    return true;
}

int main() {
    string p_str;
    const double M = 0.261497212847642783755426838608695852851; // Meissel-Mertens constant
    
    while (cin >> p_str) {
        // p 是大質數，我們用質數定理近似：sum(1/q) ≈ ln(ln(p)) + M
        // p = m * 10^e, where 1 <= m < 10
        int e = p_str.size() - 1;
        double m = 0.0;
        // 將 p_str 轉換為 m (前幾位有效數字)
        int precision = min((int)p_str.size(), 18);
        string m_str = p_str.substr(0, precision);
        m = stoll(m_str) / pow(10, precision - 1);
        
        // ln(p) = ln(m) + e * ln(10)
        double ln_p = log(m) + e * log(10.0);
        
        // ln(ln(p))
        double ln_ln_p = log(ln_p);
        
        // sum ≈ ln(ln(p)) + M
        double result = ln_ln_p + M;
        
        // 四捨五入到小數點後第三位
        cout << fixed << setprecision(3) << result << endl;
    }
    
    return 0;
}
