#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    while (cin >> t) {
        while (t--) {
            int n, m;
            cin >> n >> m;
            cout << (n / 3) * (m / 3) << "\n";
        }
    }
    
    return 0;
}
