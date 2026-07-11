#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        while (n--) {
            string s;
            cin >> s;
            long long a = 0, b = 0;
            char op = 0;
            
            for (char c : s) {
                if (c >= '0' && c <= '9') {
                    if (op == 0) {
                        a = a * 10 + (c - '0');
                    } else {
                        b = b * 10 + (c - '0');
                    }
                } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
                    op = c;
                }
            }
            
            long long ans = 0;
            switch (op) {
                case '+': ans = a + b; break;
                case '-': ans = a - b; break;
                case '*': ans = a * b; break;
                case '/': ans = a / b; break;
                case '%': ans = a % b; break;
            }
            
            cout << ans << "\n";
        }
    }
    
    return 0;
}
