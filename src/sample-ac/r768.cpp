#include <iostream>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long x;
    while (cin >> x && x != 0) {
        bool neg = false;
        if (x < 0) {
            neg = true;
            x = -x;
        }
        
        long long g = 0;
        for (long long i = 2; i * i <= x; ++i) {
            if (x % i == 0) {
                int cnt = 0;
                while (x % i == 0) {
                    x /= i;
                    cnt++;
                }
                g = gcd(g, (long long)cnt);
            }
        }
        if (x > 1) {
            g = gcd(g, 1LL);
        }
        
        if (g == 0) g = 1;
        
        if (neg) {
            while (g % 2 == 0) {
                g /= 2;
            }
        }
        
        cout << g << "\n";
    }
    
    return 0;
}
