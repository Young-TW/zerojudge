#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string multiplyBy8(string s) {
    string res = "";
    int carry = 0;
    for (int i = s.length() - 1; i >= 0; --i) {
        int prod = (s[i] - '0') * 8 + carry;
        res += char(prod % 10 + '0');
        carry = prod / 10;
    }
    while (carry) {
        res += char(carry % 10 + '0');
        carry /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string addStrings(string a, string b) {
    string res = "";
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }
        res += char(sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string divideBy2(string s) {
    string res = "";
    int rem = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        int cur = rem * 10 + (s[i] - '0');
        res += char(cur / 2 + '0');
        rem = cur % 2;
    }
    size_t start = 0;
    while (start < res.length() - 1 && res[start] == '0') {
        start++;
    }
    return res.substr(start);
}

void solve(int n) {
    string pow8 = "1";
    for (int i = 0; i < n; ++i) {
        pow8 = multiplyBy8(pow8);
    }
    
    string pow10 = "1";
    for (int i = 0; i < n; ++i) {
        pow10 += "0";
    }
    
    string sum = addStrings(pow10, pow8);
    string ans = divideBy2(sum);
    
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n && n) {
        solve(n);
    }
    return 0;
}
