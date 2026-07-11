#include <iostream>
#include <vector>

using namespace std;

struct BigInt {
    vector<int> digits;

    BigInt() {}

    BigInt(long long val) {
        if (val == 0) {
            digits.push_back(0);
        }
        while (val > 0) {
            digits.push_back(val % 10);
            val /= 10;
        }
    }

    bool divisible(int divisor) const {
        int rem = 0;
        for (int i = (int)digits.size() - 1; i >= 0; --i) {
            rem = (rem * 10 + digits[i]) % divisor;
        }
        return rem == 0;
    }

    void divide(int divisor) {
        int rem = 0;
        for (int i = (int)digits.size() - 1; i >= 0; --i) {
            int cur = rem * 10 + digits[i];
            digits[i] = cur / divisor;
            rem = cur % divisor;
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    void multiply(int multiplier) {
        int carry = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            int prod = digits[i] * multiplier + carry;
            digits[i] = prod % 10;
            carry = prod / 10;
        }
        while (carry > 0) {
            digits.push_back(carry % 10);
            carry /= 10;
        }
    }

    void print() const {
        for (int i = (int)digits.size() - 1; i >= 0; --i) {
            cout << digits[i];
        }
        cout << "\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, n;
    while (cin >> a >> n) {
        BigInt v(a);
        for (int i = 2; i <= n; ++i) {
            int divisor = i - 1;
            if (v.divisible(divisor)) {
                v.divide(divisor);
            } else {
                v.multiply(divisor);
            }
        }
        v.print();
    }
    return 0;
}
