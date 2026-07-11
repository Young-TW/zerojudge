#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        long long a = 1;
        for (long long i = 1; i * i <= n; ++i) {
            if (n % (i * i) == 0) {
                a = i;
            }
        }
        
        long long b = n / (a * a);
        
        if (b == 1) {
            cout << a << "\n";
        } else if (a == 1) {
            cout << "sqrt(" << b << ")\n";
        } else {
            cout << a << " sqrt(" << b << ")\n";
        }
    }
    
    return 0;
}
