#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long L;
    while (cin >> L) {
        long long m = (long long)sqrt((double)L);
        while (m * m < L) {
            m++;
        }
        while (m * m >= L && (m - 1) * (m - 1) >= L) {
            m--;
        }
        
        if (m * m == L) {
            cout << 2 * m - 1 << "\n";
        } else if (L <= m * m - m) {
            cout << 2 * m - 2 << "\n";
        } else {
            cout << 2 * m - 1 << "\n";
        }
    }
    
    return 0;
}
