#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            vector<int> p(n);
            for (int i = 0; i < n; ++i) {
                cin >> p[i];
            }
            sort(p.begin(), p.end());
            long long ans = 0;
            for (int i = 0; i < n; ++i) {
                long long diff = p[i] - (i + 1);
                if (diff < 0) diff = -diff;
                ans += diff;
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}
