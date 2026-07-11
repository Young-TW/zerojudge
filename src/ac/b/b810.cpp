#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int y;
    while (cin >> y) {
        if (y == 1) {
            cout << 1 << endl;
            continue;
        }
        // answer = (y+1) * 2^(y-2)
        vector<int> digits; // LSB first, decimal
        digits.push_back(1);
        int exp = y - 2;
        for (int i = 0; i < exp; i++) {
            int carry = 0;
            for (size_t j = 0; j < digits.size(); j++) {
                int v = digits[j] * 2 + carry;
                digits[j] = v % 10;
                carry = v / 10;
            }
            while (carry) {
                digits.push_back(carry % 10);
                carry /= 10;
            }
        }
        int m = y + 1;
        int carry = 0;
        for (size_t j = 0; j < digits.size(); j++) {
            int v = digits[j] * m + carry;
            digits[j] = v % 10;
            carry = v / 10;
        }
        while (carry) {
            digits.push_back(carry % 10);
            carry /= 10;
        }
        string s;
        for (int j = (int)digits.size() - 1; j >= 0; j--) {
            s += char('0' + digits[j]);
        }
        cout << s << endl;
    }
    return 0;
}
