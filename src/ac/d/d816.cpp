#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> A(m);
        for (int i = 0; i < m; ++i) {
            cin >> A[i];
        }
        
        for (int t = 0; t < m - n; ++t) {
            int diff = A[t + n] - A[t];
            int abs_diff = diff < 0 ? -diff : diff;
            int ans = (abs_diff + n - 1) / n;
            
            if (t > 0) {
                cout << " ";
            }
            cout << ans;
        }
        cout << "\n";
    }
    
    return 0;
}
