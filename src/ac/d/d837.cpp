#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        long long catalan = 1;
        for (int i = 0; i < n; ++i) {
            catalan = catalan * 2 * (2 * i + 1) / (i + 2);
        }
        cout << catalan << "\n";
    }
    
    return 0;
}
