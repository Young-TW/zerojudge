#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string trimLeadingZeros(string s) {
    int nonZero = 0;
    while (nonZero < (int)s.length() - 1 && s[nonZero] == '0') {
        nonZero++;
    }
    return s.substr(nonZero);
}

string subOne(string s) {
    int borrow = 1;
    for (int i = s.length() - 1; i >= 0 && borrow; i--) {
        int diff = (s[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        s[i] = diff + '0';
    }
    return trimLeadingZeros(s);
}

string multiply(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";
    int n = a.length();
    int m = b.length();
    vector<int> res(n + m, 0);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int p1 = i + j, p2 = i + j + 1;
            int sum = mul + res[p2];
            res[p2] = sum % 10;
            res[p1] += sum / 10;
        }
    }
    int start = 0;
    while (start < (int)res.size() - 1 && res[start] == 0) {
        start++;
    }
    string ans = "";
    for (int i = start; i < (int)res.size(); i++) {
        ans += (res[i] + '0');
    }
    return ans;
}

string addTwo(string s) {
    int carry = 2;
    for (int i = s.length() - 1; i >= 0 && carry; i--) {
        int sum = (s[i] - '0') + carry;
        s[i] = sum % 10 + '0';
        carry = sum / 10;
    }
    if (carry) {
        s = string(1, char(carry + '0')) + s;
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string n;
    while (cin >> n) {
        n = trimLeadingZeros(n);
        if (n == "0") {
            cout << 1 << "\n";
        } else {
            string n_minus_1 = subOne(n);
            string prod = multiply(n, n_minus_1);
            string ans = addTwo(prod);
            cout << ans << "\n";
        }
    }
    return 0;
}
