#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        if (n < 2) {
            cout << -1 << "\n";
            continue;
        }
        
        long long min_val = a[0];
        int min_idx = 0;
        long long max_profit = -1;
        int buy = -1, sell = -1;
        
        for (int i = 1; i < n; ++i) {
            if (a[i] > min_val) {
                long long profit = a[i] - min_val;
                if (profit > max_profit) {
                    max_profit = profit;
                    buy = min_idx;
                    sell = i;
                }
            } else if (a[i] < min_val) {
                min_val = a[i];
                min_idx = i;
            }
        }
        
        if (max_profit == -1) {
            cout << -1 << "\n";
        } else {
            cout << buy + 1 << " " << sell + 1 << "\n";
        }
    }
    
    return 0;
}
