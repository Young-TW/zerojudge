#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// 移除字串中的逗號
string removeCommas(const string& s) {
    string res;
    for (char c : s) {
        if (c != ',') {
            res += c;
        }
    }
    return res;
}

int main() {
    int N;
    if (!(cin >> N)) return 0;

    while (N--) {
        string numStr;
        int sigFigs;
        cin >> numStr >> sigFigs;

        string cleanNum = removeCommas(numStr);
        
        // 找出小數點位置
        size_t dotPos = cleanNum.find('.');
        
        // 找出第一個非零數字的位置
        size_t firstNonZero = string::npos;
        for (size_t i = 0; i < cleanNum.length(); ++i) {
            if (cleanNum[i] >= '1' && cleanNum[i] <= '9') {
                firstNonZero = i;
                break;
            }
        }

        // 處理數字為 0 的特殊情況 (雖然題目範例似乎沒有 0，但需考慮)
        if (firstNonZero == string::npos) {
            // 如果全是 0
            cout << "0.";
            for (int i = 0; i < sigFigs - 1; ++i) cout << "0";
            cout << "x10(0)" << endl;
            continue;
        }

        // 計算指數
        int exponent = 0;
        if (dotPos == string::npos) {
            // 沒有小數點，例如 300000
            // 第一個非零數字在 firstNonZero
            // 數字長度為 len
            // 指數 = (len - 1) - firstNonZero
            exponent = (int)cleanNum.length() - 1 - (int)firstNonZero;
        } else {
            if (firstNonZero < dotPos) {
                // 數字大於等於 1，例如 300.5
                // 指數 = (dotPos - 1) - firstNonZero
                exponent = (int)dotPos - 1 - (int)firstNonZero;
            } else {
                // 數字小於 1，例如 0.000909
                // firstNonZero > dotPos
                // 指數 = -(firstNonZero - dotPos)
                // 注意：0.000909 -> 9.09 * 10^-4
                // dotPos=1, firstNonZero=5 (0.0009...)
                // 5 - 1 = 4, 指數是 -4? 
                // 讓我們重新檢查: 0.000909 = 9.09 * 10^-4
                // 小數點後有 3 個零，然後是 9。
                // 從原小數點移動到 9 後面需要移動 4 位。
                // 公式：exponent = -(firstNonZero - dotPos) 如果是 0.xxx
                // 0.000909: dotPos=1, firstNonZero=5 ('9')
                // exponent = -(5 - 1) = -4. 正確。
                exponent = -((int)firstNonZero - (int)dotPos);
            }
        }

        // 構建有效數字部分
        // 收集所有數字字符
        vector<char> digits;
        for (char c : cleanNum) {
            if (isdigit(c)) {
                digits.push_back(c);
            }
        }

        // 從第一個非零數字開始取 sigFigs 位，並進行四捨五入
        // 我們需要取 sigFigs + 1 位來判斷是否需要進位
        int startIdx = 0;
        // 在 digits 向量中找到對應的起始索引
        // cleanNum 中的 firstNonZero 對應到 digits 中的哪個索引？
        // digits 只包含數字，所以我們只需要數 cleanNum 中 firstNonZero 之前有多少個數字
        int count = 0;
        for (size_t i = 0; i < firstNonZero; ++i) {
            if (isdigit(cleanNum[i])) {
                count++;
            }
        }
        startIdx = count;

        // 現在我們需要從 digits[startIdx] 開始取 sigFigs 位
        // 為了四捨五入，我們看第 sigFigs + 1 位
        string resultDigits = "";
        
        // 如果剩餘的數字不夠 sigFigs，補零嗎？不，題目是給定數字取有效位數
        // 但輸入可能是整數或小數，我們已經提取了所有數字
        // 如果 digits 從 startIdx 開始的數量少於 sigFigs，這意味著原始數字的有效數字不足？
        // 不，題目說 "第二數字表示取幾位有效數字"，通常意味著我們要格式化輸出。
        // 如果原始數字有效位數不足，我們直接輸出並補零嗎？
        // 範例 1: 300,000,000 (9 個 0, 1 個 3)，取 4 位 -> 3.000
        // 這意味著如果數字不夠，要補 0。
        
        // 準備一個足夠長的數字序列用於四捨五入
        // 我們需要 sigFigs 位，加上下一位用於判斷進位
        vector<int> nums;
        for (size_t i = startIdx; i < digits.size(); ++i) {
            nums.push_back(digits[i] - '0');
        }
        
        // 如果 nums 的大小小於 sigFigs，補 0 直到大小為 sigFigs + 1 (為了方便處理進位邏輯)
        // 實際上我們只需要確保能取到 sigFigs 位，以及第 sigFigs+1 位
        while (nums.size() < (size_t)sigFigs + 1) {
            nums.push_back(0);
        }

        // 執行四捨五入
        // 從最後一位需要保留的下一位開始檢查
        // 我們需要保留前 sigFigs 位
        // 檢查第 sigFigs 位 (index = sigFigs - 1) 的下一位 (index = sigFigs)
        int carry = 0;
        if (nums[sigFigs] >= 5) {
            carry = 1;
        }

        string finalDigits = "";
        for (int i = sigFigs - 1; i >= 0; --i) {
            int sum = nums[i] + carry;
            if (sum >= 10) {
                carry = 1;
                sum %= 10;
            } else {
                carry = 0;
            }
            finalDigits += (char)('0' + sum);
        }
        
        if (carry) {
            finalDigits += '1';
            // 如果進位導致位數增加，指數需要 +1
            exponent++;
        }
        
        reverse(finalDigits.begin(), finalDigits.end());

        // 格式化輸出
        // 格式：d.dddx10(n)
        cout << finalDigits[0];
        if (sigFigs > 1) {
            cout << ".";
            for (int i = 1; i < (int)finalDigits.length(); ++i) {
                cout << finalDigits[i];
            }
            // 如果因為進位導致長度變短（不太可能，除非邏輯錯誤）或者需要補零
            // 上面的邏輯中，如果進位，finalDigits 長度會是 sigFigs 或 sigFigs+1
            // 如果沒進位，長度是 sigFigs
            // 等等，如果 nums 原本就不夠長，我們補了 0，所以 finalDigits 長度應該是 sigFigs (沒進位) 或 sigFigs+1 (進位且首位變 10->1.0?)
            // 讓我們重新檢查進位邏輯。
            // 例子：9.95 取 2 位。nums = [9, 9, 5]. sigFigs=2.
            // i=1: 9+0 (carry init 0? No, check index 2 which is 5 -> carry=1). 
            // Wait, logic flow:
            // check nums[2] (5) >= 5 -> carry = 1.
            // loop i from 1 down to 0.
            // i=1: nums[1]=9, sum=10 -> digit=0, carry=1. finalDigits="0"
            // i=0: nums[0]=9, sum=10 -> digit=0, carry=1. finalDigits="00"
            // loop ends. carry=1. finalDigits+="1" -> "001". Reverse -> "100".
            // Output: 1.00 x 10^(exp+1). Correct.
            
            // 另一種情況：1.234 取 3 位。nums=[1,2,3,4]. sigFigs=3.
            // nums[3]=4 < 5 -> carry=0.
            // i=2: 3 -> "3"
            // i=1: 2 -> "32"
            // i=0: 1 -> "321"
            // Reverse -> "123". Output 1.23. Correct.
            
            // 補零情況：300,000,000 取 4 位。
            // cleanNum = "300000000", firstNonZero=0 ('3').
            // digits = ['3', '0', '0', ...]
            // startIdx = 0.
            // nums = [3, 0, 0, 0, 0, ...] (補零到 5 個)
            // sigFigs = 4. Check nums[4] (0) -> carry=0.
            // Loop i=3 to 0: 0, 0, 0, 3. finalDigits="0003". Reverse="3000".
            // Output: 3.000. Correct.
        }
        
        cout << "x10(" << exponent << ")" << endl;
    }

    return 0;
}
