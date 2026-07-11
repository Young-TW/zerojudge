#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n != 0) {
        vector<int> prices(n);
        for (int i = 0; i < n; ++i) {
            cin >> prices[i];
        }
        
        long long max_profit = 0;
        for (int i = 1; i < n; ++i) {
            if (prices[i] > prices[i - 1]) {
                max_profit += prices[i] - prices[i - 1];
            }
        }
        
        cout << max_profit << "\n";
    }
    
    return 0;
}
