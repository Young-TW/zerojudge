#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    while (cin >> m) {
        cout << (25 - m + 60) % 60 << "\n";
    }
    
    return 0;
}
