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
        res.push_back((sum % 10) + '0');
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<string> dp(101);
    dp[1] = "1";
    if (100 >= 2) dp[2] = "2";
    for (int i = 3; i <= 100; ++i) {
        dp[i] = add(dp[i-1], dp[i-2]);
    }
    
    int n;
    while (cin >> n) {
        cout << dp[n] << "\n";
    }
    
    return 0;
}
