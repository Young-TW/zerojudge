#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    while (cin >> n >> m && (n || m)) {
        if (n > m) {
            swap(n, m);
        }
        
        long long ans = n * m * (n + m - 2);
        long long diag = 2 * n * (n - 1) * (3 * m - n - 1);
        diag /= 3;
        ans += diag;
        
        cout << ans << "\n";
    }
    
    return 0;
}
