#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        long long a = 1, b = 1;
        for (int i = 2; i <= n; ++i) {
            long long c = a + b;
            a = b;
            b = c;
        }
        cout << a << ":" << b << "\n";
    }
    
    return 0;
}
