#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    while (cin >> n >> m) {
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        vector<long long> A(m);
        for (int i = 0; i < m; ++i) {
            cin >> A[i];
        }
        
        sort(A.begin(), A.end());
        
        long long k = m / n;
        long long ans = 0;
        for (int i = 0; i < m; ++i) {
            long long diff = A[i] - (i / k + 1);
            if (diff < 0) diff = -diff;
            ans += diff;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
