#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        while (n--) {
            long long a, b, c, d, e, f;
            cin >> a >> b >> c >> d >> e >> f;
            long long det = a * e - b * d;
            long long x = (c * e - b * f) / det;
            long long y = (a * f - c * d) / det;
            cout << x << " " << y << "\n";
        }
    }
    
    return 0;
}
