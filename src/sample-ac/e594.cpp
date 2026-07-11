#include <iostream>

using namespace std;

long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

long long floor_div(long long a, long long b) {
    long long q = a / b, r = a % b;
    if (r != 0 && ((r < 0) != (b < 0))) q--;
    return q;
}

long long ceil_div(long long a, long long b) {
    long long q = a / b, r = a % b;
    if (r != 0 && ((r < 0) == (b < 0))) q++;
    return q;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n;
    while (cin >> n && n) {
        long long c1, n1, c2, n2;
        cin >> c1 >> n1 >> c2 >> n2;
        
        long long x0, y0;
        long long g = extgcd(n1, n2, x0, y0);
        
        if (n % g != 0) {
            cout << "failed\n";
            continue;
        }
        
        long long n_prime = n / g;
        long long n1_prime = n1 / g;
        long long n2_prime = n2 / g;
        
        long long x_base = x0 * n_prime;
        long long y_base = y0 * n_prime;
        
        long long k_min = ceil_div(-x_base, n2_prime);
        long long k_max = floor_div(y_base, n1_prime);
        
        if (k_min > k_max) {
            cout << "failed\n";
            continue;
        }
        
        long long A = c1 * n2_prime - c2 * n1_prime;
        long long k;
        if (A > 0) {
            k = k_min;
        } else if (A < 0) {
            k = k_max;
        } else {
            k = k_min;
        }
        
        long long x = x_base + k * n2_prime;
        long long y = y_base - k * n1_prime;
        
        cout << x << " " << y << "\n";
    }
    
    return 0;
}
