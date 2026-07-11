#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        long long xor_sum = 0;
        for (int i = 0; i < n; i++) {
            long long p;
            cin >> p;
            xor_sum ^= p;
        }
        cout << (xor_sum != 0 ? "Yes" : "No") << "\n";
    }
    
    return 0;
}
