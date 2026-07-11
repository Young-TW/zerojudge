#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    char k;
    while (cin >> k) {
        string s;
        cin >> s;
        if (k == 'T') {
            if (s.length() <= 18) {
                ll n = 0;
                for (char c : s) n = n * 10 + (c - '0');
                string res = "";
                if (n == 0) res = "0";
                while (n > 0) {
                    int digit = n % 9;
                    if (digit >= 4) digit++;
                    res += (char)('0' + digit);
                    n /= 9;
                }
                reverse(res.begin(), res.end());
                cout << res << "\n";
            } else {
                string res = "";
                string current = s;
                while (current != "0") {
                    int rem = 0;
                    string next = "";
                    for (int i = 0; i < current.length(); ++i) {
                        int cur = rem * 10 + (current[i] - '0');
                        next += (char)(cur / 9 + '0');
                        rem = cur % 9;
                    }
                    int digit = rem;
                    if (digit >= 4) digit++;
                    res += (char)('0' + digit);
                    
                    int first_non_zero = 0;
                    while (first_non_zero < next.length() - 1 && next[first_non_zero] == '0') {
                        first_non_zero++;
                    }
                    current = next.substr(first_non_zero);
                }
                reverse(res.begin(), res.end());
                cout << res << "\n";
            }
        } else if (k == 'F') {
            if (s.length() <= 18) {
                ll res = 0;
                for (char c : s) {
                    int digit = c - '0';
                    if (digit > 4) digit--;
                    res = res * 9 + digit;
                }
                cout << res << "\n";
            } else {
                string res = "0";
                for (char c : s) {
                    int digit = c - '0';
                    if (digit > 4) digit--;
                    int carry = digit;
                    for (int i = res.length() - 1; i >= 0; --i) {
                        int cur = (res[i] - '0') * 9 + carry;
                        res[i] = cur % 10 + '0';
                        carry = cur / 10;
                    }
                    while (carry > 0) {
                        res = (char)(carry % 10 + '0') + res;
                        carry /= 10;
                    }
                }
                cout << res << "\n";
            }
        }
    }
    return 0;
}
