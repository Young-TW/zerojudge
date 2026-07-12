#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 1) {
            int a;
            cin >> a;
            cout << "0\n";
        } else {
            for (int i = 0; i < n; ++i) {
                int a;
                cin >> a;
                if (i < n - 1) {
                    if (i > 0) cout << " ";
                    cout << a * (n - 1 - i);
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
