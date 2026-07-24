#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <algorithm>

using namespace std;

// 大數結構：十進位，低位在前
struct BigInt {
    vector<int> digits;

    BigInt() {}
    BigInt(long long v) {
        if (v == 0) digits.push_back(0);
        while (v > 0) {
            digits.push_back(v % 10);
            v /= 10;
        }
    }

    void add(const BigInt& other) {
        int carry = 0;
        int n = max(digits.size(), other.digits.size());
        for (int i = 0; i < n || carry; ++i) {
            if (i == (int)digits.size()) digits.push_back(0);
            int d = digits[i] + carry + (i < (int)other.digits.size() ? other.digits[i] : 0);
            digits[i] = d % 10;
            carry = d / 10;
        }
    }

    void print() const {
        if (digits.empty()) {
            cout << 0;
            return;
        }
        for (int i = (int)digits.size() - 1; i >= 0; --i) {
            cout << digits[i];
        }
    }
};

int parseChar(char c, int n) {
    if (c == '?') return -1;
    if (c >= '1' && c <= '9') {
        int val = c - '1';
        if (val >= n) return -2; // invalid
        return val;
    }
    if (c >= 'A' && c <= 'O') {
        int val = c - 'A' + 9;
        if (val >= n) return -2;
        return val;
    }
    return -2;
}

int main() {
    string line;
    while (cin >> line) {
        int n = line.size();
        vector<int> board(n);
        bool invalid = false;
        for (int i = 0; i < n; ++i) {
            board[i] = parseChar(line[i], n);
            if (board[i] == -2) {
                invalid = true;
            }
        }

        if (invalid) {
            cout << 0 << endl;
            continue;
        }

        // dp[col] = number of ways ending at current row with queen at col
        vector<BigInt> dp(n);
        
        // Initialize first row
        if (board[0] == -1) {
            for (int c = 0; c < n; ++c) {
                dp[c] = BigInt(1);
            }
        } else {
            dp[board[0]] = BigInt(1);
        }

        // Process remaining rows
        for (int i = 1; i < n; ++i) {
            vector<BigInt> new_dp(n);
            for (int cur = 0; cur < n; ++cur) {
                if (board[i] != -1 && board[i] != cur) continue;
                
                for (int prev = 0; prev < n; ++prev) {
                    if (dp[prev].digits.empty()) continue;
                    
                    // Check constraint: |cur - prev| > 1
                    if (abs(cur - prev) > 1) {
                        new_dp[cur].add(dp[prev]);
                    }
                }
            }
            dp = new_dp;
        }

        BigInt total(0);
        for (int c = 0; c < n; ++c) {
            total.add(dp[c]);
        }
        total.print();
        cout << endl;
    }
    return 0;
}
