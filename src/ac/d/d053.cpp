#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, n;
    while (cin >> m >> n) {
        cout << m * n - 1 << "\n";
    }
    
    return 0;
}
