#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// 將費氏進位字串轉換為大整數 (用 vector<int> 儲存，低位在前)
// 由於輸入長度可達 100，對應的數值非常大，必須使用大整數運算
vector<int> fibToBigInt(const string& s) {
    if (s.empty()) return {0};
    
    // 預先計算足夠的費氏數列
    int n = s.length();
    vector<vector<int>> fibs(n + 2);
    
    // F[0] = 1, F[1] = 1
    fibs[0] = {1};
    fibs[1] = {1};
    
    for (int i = 2; i <= n; i++) {
        // 大整數加法
        vector<int>& a = fibs[i-1];
        vector<int>& b = fibs[i-2];
        vector<int> c;
        int carry = 0;
        int maxLen = max(a.size(), b.size());
        
        for (int j = 0; j < maxLen || carry; j++) {
            int sum = carry;
            if (j < a.size()) sum += a[j];
            if (j < b.size()) sum += b[j];
            c.push_back(sum % 10);
            carry = sum / 10;
        }
        fibs[i] = c;
    }
    
    // 根據輸入字串計算總和
    // 字串最右邊對應 F[0], 往左對應 F[1], F[2]...
    vector<int> result = {0};
    
    for (int i = 0; i < n; i++) {
        if (s[n - 1 - i] == '1') {
            // 加上 fibs[i]
            vector<int>& addend = fibs[i];
            int carry = 0;
            int maxLen = max(result.size(), addend.size());
            
            for (int j = 0; j < maxLen || carry; j++) {
                int sum = carry;
                if (j < result.size()) sum += result[j];
                if (j < addend.size()) sum += addend[j];
                
                if (j < result.size()) {
                    result[j] = sum % 10;
                } else {
                    result.push_back(sum % 10);
                }
                carry = sum / 10;
            }
        }
    }
    
    // 移除前導零
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    
    return result;
}

// 大整數加法
vector<int> bigIntAdd(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int carry = 0;
    int maxLen = max(a.size(), b.size());
    
    for (int i = 0; i < maxLen || carry; i++) {
        int sum = carry;
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    
    return result;
}

// 將大整數轉換回費氏進位表示法
string bigIntToFib(vector<int> num) {
    if (num.empty() || (num.size() == 1 && num[0] == 0)) {
        return "0";
    }
    
    // 移除前導零
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
    
    if (num.size() == 1 && num[0] == 0) {
        return "0";
    }
    
    // 生成足夠大的費氏數列直到超過 num
    vector<vector<int>> fibs;
    fibs.push_back({1}); // F[0]
    fibs.push_back({1}); // F[1]
    
    while (true) {
        vector<int>& a = fibs[fibs.size() - 1];
        vector<int>& b = fibs[fibs.size() - 2];
        vector<int> c;
        int carry = 0;
        int maxLen = max(a.size(), b.size());
        
        for (int i = 0; i < maxLen || carry; i++) {
            int sum = carry;
            if (i < a.size()) sum += a[i];
            if (i < b.size()) sum += b[i];
            c.push_back(sum % 10);
            carry = sum / 10;
        }
        
        // 檢查 c 是否大於 num
        if (c.size() > num.size() || (c.size() == num.size() && c > num)) {
            break;
        }
        fibs.push_back(c);
    }
    
    // 貪婪算法：從最大的費氏數開始，能減就減
    string result = "";
    int fibIndex = fibs.size() - 1;
    
    for (int i = fibIndex; i >= 0; i--) {
        // 檢查 num 是否 >= fibs[i]
        bool canSubtract = false;
        if (num.size() > fibs[i].size()) {
            canSubtract = true;
        } else if (num.size() == fibs[i].size()) {
            canSubtract = (num >= fibs[i]);
        }
        
        if (canSubtract) {
            // num -= fibs[i]
            int borrow = 0;
            for (int j = 0; j < fibs[i].size() || borrow; j++) {
                int sub = borrow;
                if (j < fibs[i].size()) sub += fibs[i][j];
                if (j < num.size()) sub = num[j] - sub;
                
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                
                if (j < num.size()) {
                    num[j] = sub;
                }
            }
            
            // 移除前導零
            while (num.size() > 1 && num.back() == 0) {
                num.pop_back();
            }
            
            result += '1';
        } else {
            result += '0';
        }
    }
    
    // 移除前導零
    size_t firstOne = result.find('1');
    if (firstOne == string::npos) {
        return "0";
    }
    
    return result.substr(firstOne);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a, b;
    bool firstOutput = true;
    
    while (cin >> a >> b) {
        if (!firstOutput) {
            cout << "\n";
        }
        firstOutput = false;
        
        // 轉換為大整數
        vector<int> numA = fibToBigInt(a);
        vector<int> numB = fibToBigInt(b);
        
        // 相加
        vector<int> sum = bigIntAdd(numA, numB);
        
        // 轉換回費氏進位
        string result = bigIntToFib(sum);
        
        cout << result << "\n";
    }
    
    return 0;
}
