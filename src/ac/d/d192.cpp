#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (!(cin >> t)) return 0;
    
    for (int i = 1; i <= t; ++i) {
        long long n, k;
        if (!(cin >> n >> k)) break;
        
        long long res = 0;
        for (long long j = 2; j <= n; ++j) {
            res = (res + k) % j;
        }
        
        cout << "Case " << i << ": " << res + 1 << "\n";
    }
    
    return 0;
}
