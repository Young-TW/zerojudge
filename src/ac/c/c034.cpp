#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string add(const string& a, const string& b) {
    string res;
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
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
    
    string sum = "0";
    string s;
    while (cin >> s) {
        if (s == "0") break;
        sum = add(sum, s);
    }
    cout << sum << "\n";
    return 0;
}
