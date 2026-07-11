#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string mul(const string& a, int b) {
    string res;
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; --i) {
        int prod = (a[i] - '0') * b + carry;
        res.push_back((prod % 10) + '0');
        carry = prod / 10;
    }
    while (carry) {
        res.push_back((carry % 10) + '0');
        carry /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long M;
    while (cin >> M) {
        unsigned long long sq = M * M;
        string s = to_string(sq);
        string ans = mul(s, 25);
        cout << ans << "\n";
    }
    return 0;
}
