#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int k, x1, y1, x2, y2;
    while (cin >> k >> x1 >> y1 >> x2 >> y2) {
        long long p = 0;
        int v = k;
        while (v > 0) {
            p += v;
            if (p % x1 == 0) {
                v -= y1;
            }
            if (p % x2 == 0) {
                v -= y2;
            }
        }
        cout << p << "\n";
    }
    
    return 0;
}
