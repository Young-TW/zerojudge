#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string add(const string& a, const string& b) {
    string res;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 10;
        res.push_back((sum % 10) + '0');
    }
    reverse(res.begin(), res.end());
    return res;
}

string sub(const string& a, const string& b) {
    string res;
    int borrow = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    while (i >= 0) {
        int diff = (a[i--] - '0') - borrow;
        if (j >= 0) diff -= (b[j--] - '0');
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.push_back(diff + '0');
    }
    while (res.length() > 1 && res.back() == '0') {
        res.pop_back();
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string a, op, b;
    while (cin >> a >> op >> b) {
        if (op == "+") {
            cout << add(a, b) << "\n";
        } else if (op == "-") {
            cout << sub(a, b) << "\n";
        }
    }
    return 0;
}
