#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        int xa = -1, xb = -1;
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            if (xa == -1) {
                xa = x;
                cout << "A\n";
            } else if (xb == -1) {
                if (x == xa) {
                    cout << "A\n";
                } else {
                    xb = x;
                    cout << "B\n";
                }
            } else {
                if (abs(x - xa) <= abs(x - xb)) {
                    cout << "A\n";
                } else {
                    cout << "B\n";
                }
            }
        }
    }
    
    return 0;
}
