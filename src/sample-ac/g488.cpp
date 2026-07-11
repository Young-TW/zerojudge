#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long x;
    while (cin >> x) {
        cout << x * (x * x + 2) / 3 << '\n';
    }
    
    return 0;
}
