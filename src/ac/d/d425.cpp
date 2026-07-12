#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long calculate_unsatisfaction(long long x, long long k) {
    return (x - 2) * (x - 1) / 2 + (k - x) * (k - x + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long k;
    while (cin >> k) {
        long long x0 = (4 * k + 5) / 6;
        long long min_f = -1;
        vector<long long> ans;
        
        for (long long x = max(2LL, x0 - 2); x <= min(k, x0 + 2); ++x) {
            long long current_f = calculate_unsatisfaction(x, k);
            if (min_f == -1 || current_f < min_f) {
                min_f = current_f;
                ans.clear();
                ans.push_back(x);
            } else if (current_f == min_f) {
                ans.push_back(x);
            }
        }
        
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i > 0) cout << " ";
            cout << ans[i];
        }
        cout << "\n";
    }
    
    return 0;
}
