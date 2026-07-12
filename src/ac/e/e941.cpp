#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long my_abs(long long x) {
    return x < 0 ? -x : x;
}

void print_result(long long num, long long den) {
    if (num == 0) {
        den = 1;
    } else {
        long long g = gcd(my_abs(num), my_abs(den));
        num /= g;
        den /= g;
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }
    cout << num << "/" << den << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string token;
    while (cin >> token) {
        size_t slash_pos = token.find('/');
        long long a = stoll(token.substr(0, slash_pos));
        long long b = stoll(token.substr(slash_pos + 1));
        long long num = a;
        long long den = b;
        
        while (cin >> token) {
            if (token == "+" || token == "-") {
                char op = token[0];
                if (!(cin >> token)) break; 
                size_t sp = token.find('/');
                long long na = stoll(token.substr(0, sp));
                long long nb = stoll(token.substr(sp + 1));
                
                if (op == '+') {
                    num = num * nb + na * den;
                } else {
                    num = num * nb - na * den;
                }
                den = den * nb;
                
                long long g = gcd(my_abs(num), my_abs(den));
                if (g != 0) {
                    num /= g;
                    den /= g;
                }
            } else {
                print_result(num, den);
                
                slash_pos = token.find('/');
                a = stoll(token.substr(0, slash_pos));
                b = stoll(token.substr(slash_pos + 1));
                num = a;
                den = b;
            }
        }
        print_result(num, den);
    }
    
    return 0;
}
