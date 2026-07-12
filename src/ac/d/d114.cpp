#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct BigInt {
    vector<int> digits;
    BigInt(int x = 0) {
        if (x > 0) {
            digits.push_back(x);
        }
    }
    void multiply(int x) {
        long long carry = 0;
        for (size_t i = 0; i < digits.size(); i++) {
            long long prod = (long long)digits[i] * x + carry;
            digits[i] = prod % 1000000000;
            carry = prod / 1000000000;
        }
        while (carry > 0) {
            digits.push_back(carry % 1000000000);
            carry /= 1000000000;
        }
    }
    void print_digits() {
        if (digits.empty()) {
            cout << 0 << "\n";
            return;
        }
        string s;
        s += to_string(digits.back());
        for (int i = (int)digits.size() - 2; i >= 0; i--) {
            string part = to_string(digits[i]);
            while (part.length() < 9) part = "0" + part;
            s += part;
        }
        for (size_t i = 0; i < s.length(); i++) {
            cout << s[i] << "\n";
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    if (getline(cin, s) && !s.empty()) {
        cout << "只可意會不可言傳。\n";
        return 0;
    }
    
    BigInt ans(1);
    for (int i = 1; i <= 100; i++) {
        for (int j = 0; j < 101 - i; j++) {
            ans.multiply(i);
        }
    }
    ans.print_digits();
    
    return 0;
}
