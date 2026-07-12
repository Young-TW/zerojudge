#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long p, c, t;
    while (cin >> p >> c >> t) {
        if (p > c) {
            cout << (p - c) * t << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
    
    return 0;
}
