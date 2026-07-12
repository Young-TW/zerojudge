#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string add(const string& a, const string& b) {
    string res;
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
    dp[0] = "1";
    dp[1] = "2";
    dp[2] = "5";
    dp[3] = "13";
    
    for (int i = 4; i <= 1000; ++i) {
        string tmp = add(dp[i-1], dp[i-1]);
        tmp = add(tmp, dp[i-2]);
        dp[i] = add(tmp, dp[i-3]);
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << "\n";
    }
    
    return 0;
}
