#include <iostream>

using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long a, b, c;
    while (cin >> a >> b >> c) {
        if (a == 0 && b == 0) {
            if (c == 0) cout << "YES\n";
            else cout << "NO\n";
            continue;
        }
        if (a == 0) {
            if (c % b == 0 && c / b >= 0) cout << "YES\n";
            else cout << "NO\n";
            continue;
        }
        if (b == 0) {
            if (c % a == 0 && c / a >= 0) cout << "YES\n";
            else cout << "NO\n";
            continue;
        }

        long long x, y;
        long long g = exgcd(a, b, x, y);
        if (c % g != 0) {
            cout << "NO\n";
            continue;
        }
        
        long long a_prime = a / g;
        long long b_prime = b / g;
        long long c_prime = c / g;
        
        long long x_mod_b = (x % b_prime + b_prime) % b_prime;
        long long c_mod_b = (c_prime % b_prime + b_prime) % b_prime;
        long long x_mod = (x_mod_b * c_mod_b) % b_prime;
        
        long long y_new = (c_prime - a_prime * x_mod) / b_prime;
        
        if (y_new >= 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
