#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long n;
    while (cin >> n && n != 0) {
        unsigned long long r = sqrt(n);
        while (r * r > n) {
            r--;
        }
        while ((r + 1) * (r + 1) <= n) {
            r++;
        }
        
        if (r * r == n) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
    
    return 0;
}
