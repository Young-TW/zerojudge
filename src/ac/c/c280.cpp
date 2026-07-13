#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 1 || n == 2) {
            cout << 1 << "\n";
        } else {
            long long a = 1, b = 1;
            for (int i = 3; i <= n; ++i) {
                long long c = a + b;
                a = b;
                b = c;
            }
            cout << b << "\n";
        }
    }
    
    return 0;
}
