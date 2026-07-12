#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int a, b;
    while (cin >> a >> b) {
        cout << 2 * (a + b) << "\n";
    }
    
    return 0;
}
