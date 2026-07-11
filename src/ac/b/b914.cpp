#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            int m;
            cin >> m;
            sum += m;
        }
        cout << (sum * 2 + n) / (2 * n) << "\n";
    }
    
    return 0;
}
