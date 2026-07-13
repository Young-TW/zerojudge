#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long X, Y;
    while (cin >> X >> Y) {
        if (X == 0) {
            cout << 1 << "\n";
            continue;
        }
        
        long long Z = 100 * Y / X;
        
        if (Z >= 99) {
            cout << -1 << "\n";
            continue;
        }
        
        long long R = (100 * Y) % X;
        long long N = (X - R + (99 - Z) - 1) / (99 - Z);
        
        cout << N << "\n";
    }
    
    return 0;
}
