#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    while (cin >> a >> b) {
        long long first = (a % 2 == 1) ? a + 1 : a;
        long long last = (b % 2 == 1) ? b - 1 : b;
        
        if (first > last) {
            cout << 0 << "\n";
        } else {
            long long n = (last - first) / 2 + 1;
            cout << (first + last) * n / 2 << "\n";
        }
    }
    
    return 0;
}
