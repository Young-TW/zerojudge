#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> d(n);
        for (int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        
        long long ans = d[0];
        for (int i = 1; i < n; ++i) {
            if (d[i] > d[i - 1]) {
                ans += d[i] - d[i - 1];
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
