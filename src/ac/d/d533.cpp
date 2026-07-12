#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        while (n--) {
            double a, b, c, d;
            cin >> a >> b >> c >> d;
            
            if (fabs(b) < 1e-9 && fabs(d) < 1e-9) {
                if (a - c > 1e-9) {
                    cout << ">\n";
                } else if (fabs(a - c) < 1e-9) {
                    cout << "=\n";
                } else {
                    cout << "<\n";
                }
            } else {
                cout << "No\n";
            }
        }
    }
    
    return 0;
}
