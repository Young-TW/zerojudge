#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            long long N, R, C;
            cin >> N >> R >> C;
            
            long long r = R - 1;
            long long c = C - 1;
            
            long long x = r * N + c + 1;
            
            long long r_mod = r % 4;
            long long c_mod = c % 4;
            
            if (r_mod == c_mod || r_mod + c_mod == 3) {
                cout << N * N + 1 - x << "\n";
            } else {
                cout << x << "\n";
            }
        }
    }
    
    return 0;
}
