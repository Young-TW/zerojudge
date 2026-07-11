#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string mul(string x, string y) {
    if (x == "0" || y == "0") return "0";
    int n = x.size(), m = y.size();
    vector<int> res(n + m, 0);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            res[i + j + 1] += (x[i] - '0') * (y[j] - '0');
        }
    }
    for (int i = n + m - 1; i > 0; i--) {
        res[i - 1] += res[i] / 10;
        res[i] %= 10;
    }
    string ans = "";
    int i = 0;
    while (i < n + m && res[i] == 0) i++;
    while (i < n + m) {
        ans += to_string(res[i]);
        i++;
    }
    return ans;
}

string add(string x, string y) {
    if (x.size() < y.size()) swap(x, y);
    int n = x.size(), m = y.size();
    int carry = 0;
    string ans = "";
    for (int i = 0; i < n; i++) {
        int digit_x = x[n - 1 - i] - '0';
        int digit_y = (i < m) ? y[m - 1 - i] - '0' : 0;
        int sum = digit_x + digit_y + carry;
        ans += to_string(sum % 10);
        carry = sum / 10;
    }
    if (carry) ans += to_string(carry);
    reverse(ans.begin(), ans.end());
    return ans;
}

string power(int base, int exp) {
    string res = "1";
    string b = to_string(base);
    for (int i = 0; i < exp; i++) {
        res = mul(res, b);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, a, b;
    while (cin >> n >> a >> b) {
        if (n % 2 == 1) {
            cout << "能\n";
            cout << add(power(a, n), power(b, n)) << "\n";
        } else {
            cout << "不能\n";
        }
    }
    return 0;
}
