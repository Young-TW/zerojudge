#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    while (cin >> a >> b) {
        long long first = (a % 2 == 0) ? a : a + 1;
        long long last = (b % 2 == 0) ? b : b - 1;
        
        if (first > last) {
            cout << 0 << "\n";
        } else {
            long long n = (last - first) / 2 + 1;
            long long sum = n * (first + last) / 2;
            cout << sum << "\n";
        }
    }
    
    return 0;
}
