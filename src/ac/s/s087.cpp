#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n > 198) {
            cout << 0 << "\n";
        } else {
            cout << 199 - n << "\n";
        }
    }
    
    return 0;
}
