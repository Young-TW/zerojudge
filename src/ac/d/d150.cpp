#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    while (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<int> prices(n);
            for (int i = 0; i < n; ++i) {
                cin >> prices[i];
            }
            
            sort(prices.begin(), prices.end(), greater<int>());
            
            long long saved = 0;
            for (int i = 2; i < n; i += 3) {
                saved += prices[i];
            }
            
            cout << saved << "\n";
        }
    }
    
    return 0;
}
