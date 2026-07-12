#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string addStrings(const string& a, const string& b) {
    string res = "";
    int i = a.length() - 1;
    int j = b.length() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int digitA = (i >= 0) ? (a[i] - '0') : 0;
        int digitB = (j >= 0) ? (b[j] - '0') : 0;
        int sum = digitA + digitB + carry;
        carry = sum / 10;
        res += (sum % 10) + '0';
        i--;
        j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

void stripLeadingZeros(string& s) {
    int start = 0;
    while (start < (int)s.length() - 1 && s[start] == '0') {
        start++;
    }
    s = s.substr(start);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        while (n--) {
            string s1, s2;
            cin >> s1 >> s2;
            
            reverse(s1.begin(), s1.end());
            reverse(s2.begin(), s2.end());
            
            stripLeadingZeros(s1);
            stripLeadingZeros(s2);
            
            string sum = addStrings(s1, s2);
            
            reverse(sum.begin(), sum.end());
            stripLeadingZeros(sum);
            
            cout << sum << "\n";
        }
    }
    return 0;
}
