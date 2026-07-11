#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

long long isqrt(long long n) {
    if (n < 0) return 0;
    long long x = sqrtl(n);
    while (x * x > n) x--;
    while ((x + 1) * (x + 1) <= n) x++;
    return x;
}

long long power(long long base, long long exp) {
    long long res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res *= base;
        base *= base;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    cin.ignore();
    
    while (n--) {
        string s;
        getline(cin, s);
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        
        if (s.length() >= 4 && s.substr(0, 4) == "sqrt") {
            long long val = stoll(s.substr(4));
            cout << isqrt(val) << "\n";
        } else {
            int opPos = -1;
            char op = ' ';
            for (size_t i = 1; i < s.length(); i++) {
                if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
                    if (s[i] == '*' && i + 1 < s.length() && s[i+1] == '*') {
                        opPos = i;
                        op = '^';
                        break;
                    } else {
                        opPos = i;
                        op = s[i];
                        break;
                    }
                }
            }
            if (opPos != -1) {
                long long a = stoll(s.substr(0, opPos));
                long long b;
                if (op == '^') {
                    b = stoll(s.substr(opPos + 2));
                } else {
                    b = stoll(s.substr(opPos + 1));
                }
                
                if (op == '+') cout << a + b << "\n";
                else if (op == '-') cout << a - b << "\n";
                else if (op == '*') cout << a * b << "\n";
                else if (op == '/') cout << a / b << "\n";
                else if (op == '^') cout << power(a, b) << "\n";
            }
        }
    }
    return 0;
}
