#include <iostream>
#include <vector>
#include <string>

using namespace std;

void multiplyBy2(vector<int>& num) {
    int carry = 0;
    for (size_t i = 0; i < num.size(); ++i) {
        int product = num[i] * 2 + carry;
        num[i] = product % 10;
        carry = product / 10;
    }
    if (carry) {
        num.push_back(carry);
    }
}

void subtract2(vector<int>& num) {
    int borrow = 2;
    for (size_t i = 0; i < num.size() && borrow; ++i) {
        if (num[i] >= borrow) {
            num[i] -= borrow;
            borrow = 0;
        } else {
            num[i] = num[i] + 10 - borrow;
            borrow = 1;
        }
    }
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    bool first = true;
    while (cin >> n) {
        if (!first) {
            cout << "\n";
        }
        first = false;
        vector<int> res;
        res.push_back(1);
        for (int i = 0; i <= n; ++i) {
            multiplyBy2(res);
        }
        subtract2(res);
        for (int i = (int)res.size() - 1; i >= 0; --i) {
            cout << res[i];
        }
        cout << "\n";
    }
    return 0;
}
