#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long x;
    while (cin >> x) {
        cout << x * x + 2 * x << "\n";
    }
    
    return 0;
}
