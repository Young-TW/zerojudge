#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, N;
    while (cin >> M >> N && (M || N)) {
        int ans;
        int m = M, n = N;
        if (m > n) {
            swap(m, n);
        }
        
        if (m == 1) {
            ans = n;
        } else if (m == 2) {
            ans = (n / 4) * 4 + min(n % 4, 2) * 2;
        } else {
            ans = (m * n + 1) / 2;
        }
        
        cout << ans << " knights may be placed on a " << M << " row " << N << " column board.\n";
    }
    
    return 0;
}
