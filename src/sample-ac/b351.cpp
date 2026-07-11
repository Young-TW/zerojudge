#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (!(cin >> t)) return 0;
    
    while (t--) {
        long long N, R, C;
        if (!(cin >> N >> R >> C)) break;
        
        long long row = R - 1;
        long long col = C - 1;
        long long half = N / 2;
        long long inv2 = (N + 1) / 2;
        
        long long q = ((row - col + half) % N + N) % N;
        long long r_val = ((3 * q + half - row - col) % N + N) % N;
        long long r = (r_val * inv2) % N;
        
        long long ans = q * N + r + 1;
        cout << ans << "\n";
    }
    
    return 0;
}
