#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        if (n % 2 == 0) {
            cout << n << "\n";
        } else {
            cout << n - 1 << "\n";
        }
    }
    
    return 0;
}
