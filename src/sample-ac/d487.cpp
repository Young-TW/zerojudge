#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        cout << n << "! = ";
        if (n == 0) {
            cout << "1 = 1\n";
        } else {
            int ans = 1;
            for (int i = n; i >= 1; --i) {
                if (i == n) {
                    cout << i;
                } else {
                    cout << " * " << i;
                }
                ans *= i;
            }
            cout << " = " << ans << "\n";
        }
    }
    return 0;
}
