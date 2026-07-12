#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        while (T--) {
            long long n;
            cin >> n;
            if (n % 3 == 1) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
            }
        }
    }
    
    return 0;
}
