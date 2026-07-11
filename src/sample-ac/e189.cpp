#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long n;
    while (cin >> n) {
        while (n > 3) {
            n = (n >> 2) + (n & 3);
        }
        if (n == 0 || n == 3) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
