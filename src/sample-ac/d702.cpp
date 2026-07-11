#include <iostream>
#include <string>
#include <vector>
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
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<string> dp(1005);
    dp[1] = "1";
    dp[2] = "1";
    dp[3] = "1";
    for (int i = 4; i <= 1000; ++i) {
        dp[i] = add(dp[i-2], dp[i-3]);
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << "\n";
    }
    return 0;
}
