#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned long long a, b;
    while (cin >> a >> b) {
        cout << (a ^ b) << '\n';
    }
    
    return 0;
}
