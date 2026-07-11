#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

int getSum(const string& s) {
    int sum = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (c >= 'a' && c <= 'z') {
            sum += c - 'a' + 1;
        } else if (c >= 'A' && c <= 'Z') {
            sum += c - 'A' + 1;
        }
    }
    while (sum >= 10) {
        int temp = 0;
        while (sum > 0) {
            temp += sum % 10;
            sum /= 10;
        }
        sum = temp;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s1, s2;
    while (getline(cin, s1)) {
        if (!getline(cin, s2)) break;
        
        if (!s1.empty() && s1.back() == '\r') s1.pop_back();
        if (!s2.empty() && s2.back() == '\r') s2.pop_back();
        
        int sum1 = getSum(s1);
        int sum2 = getSum(s2);
        
        double ans = 0.0;
        if (sum1 == 0 && sum2 == 0) {
            ans = 0.0;
        } else {
            int mx = max(sum1, sum2);
            int mn = min(sum1, sum2);
            ans = (double)mn / (double)mx * 100.0;
        }
        
        cout << fixed << setprecision(2) << ans << " %\n";
    }
    return 0;
}
