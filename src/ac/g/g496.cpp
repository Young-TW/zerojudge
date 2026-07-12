#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    while (cin >> a >> b) {
        if (a == 0) {
            cout << 0 << "\n";
        } else {
            cout << (b + a - 1) / a << "\n";
        }
    }
    
    return 0;
}
