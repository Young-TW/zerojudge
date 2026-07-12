#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    while (cin >> a >> b) {
        long long L = min(a, b);
        long long R = max(a, b);
        
        long long first = (L % 2 == 0) ? L : L + 1;
        long long last = (R % 2 == 0) ? R : R - 1;
        
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
