#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            long long G, L;
            cin >> G >> L;
            if (L % G == 0) {
                cout << G << " " << L << "\n";
            } else {
                cout << -1 << "\n";
            }
        }
    }
    
    return 0;
}
