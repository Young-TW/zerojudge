#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            long long n, m;
            cin >> n >> m;
            cout << n * (2 * m - n - 1) / 2 << "\n";
        }
    }
    
    return 0;
}
