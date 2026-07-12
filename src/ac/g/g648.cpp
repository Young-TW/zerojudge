#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    while (cin >> t) {
        string s;
        getline(cin, s); // consume the rest of the line after t
        while (t--) {
            getline(cin, s);
            long long prod = 1;
            long long cur = 0;
            int sign = 1;
            bool has_num = false;
            for (char c : s) {
                if (c >= '0' && c <= '9') {
                    has_num = true;
                    cur = cur * 10 + (c - '0');
                } else if (c == '-') {
                    if (has_num) {
                        prod *= sign * cur;
                        cur = 0;
                        sign = 1;
                        has_num = false;
                    } else {
                        sign *= -1;
                    }
                } else {
                    if (has_num) {
                        prod *= sign * cur;
                        cur = 0;
                        sign = 1;
                        has_num = false;
                    }
                }
            }
            if (has_num) {
                prod *= sign * cur;
            }
            cout << prod << "\n";
        }
    }
    return 0;
}
