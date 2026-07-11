#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        while (n--) {
            long long x, y;
            cin >> x >> y;
            long long D = y - x;
            
            if (D == 0) {
                cout << 0 << "\n";
                continue;
            }
            
            long long m = sqrt(D);
            while (m * m > D) {
                m--;
            }
            while ((m + 1) * (m + 1) <= D) {
                m++;
            }
            
            if (D == m * m) {
                cout << 2 * m - 1 << "\n";
            } else if (D <= m * m + m) {
                cout << 2 * m << "\n";
            } else {
                cout << 2 * m + 1 << "\n";
            }
        }
    }
    
    return 0;
}
