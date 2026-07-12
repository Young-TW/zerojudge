#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    while (cin >> k) {
        vector<pair<int, int>> ans;
        for (int d = 1; d <= k; ++d) {
            if ((k * k) % d == 0) {
                int x = k + (k * k) / d;
                int y = k + d;
                ans.push_back({x, y});
            }
        }
        
        cout << ans.size() << "\n";
        for (const auto& p : ans) {
            cout << "1/" << k << " = 1/" << p.first << " + 1/" << p.second << "\n";
        }
    }
    
    return 0;
}
