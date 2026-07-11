#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    while (cin >> n) {
        cout << n * (n + 1) * (2 * n + 1) / 6 << "\n";
    }
    
    return 0;
}
