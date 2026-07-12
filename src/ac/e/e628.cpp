#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string m, n_str;
    char op;
    while (cin >> m >> op >> n_str) {
        long long n = 0;
        for (char c : n_str) {
            n = n * 10 + (c - '0');
        }
        
        if (op == '/') {
            string res = "";
            long long rem = 0;
            for (char c : m) {
                rem = rem * 10 + (c - '0');
                res += (char)('0' + rem / n);
                rem %= n;
            }
            size_t nonZero = res.find_first_not_of('0');
            if (nonZero == string::npos) {
                cout << "0\n";
            } else {
                cout << res.substr(nonZero) << "\n";
            }
        } else if (op == '%') {
            long long rem = 0;
            for (char c : m) {
                rem = (rem * 10 + (c - '0')) % n;
            }
            cout << rem << "\n";
        }
    }
    return 0;
}
