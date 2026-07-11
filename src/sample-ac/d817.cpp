#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string multiplyByTwo(const string& s) {
    string res = "";
    int carry = 0;
    for (int i = s.length() - 1; i >= 0; --i) {
        int digit = (s[i] - '0') * 2 + carry;
        carry = digit / 10;
        res += char(digit % 10 + '0');
    }
    if (carry > 0) {
        res += char(carry + '0');
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<string> ans(5001);
    ans[0] = "1";
    for (int i = 1; i <= 5000; ++i) {
        ans[i] = multiplyByTwo(ans[i - 1]);
    }
    
    int n;
    while (cin >> n) {
        cout << ans[n] << "\n";
    }
    
    return 0;
}
