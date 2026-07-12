#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }
        
        int max_sum = p[0], cur_max = p[0];
        int min_sum = p[0], cur_min = p[0];
        int total = p[0];
        
        for (int i = 1; i < n; ++i) {
            cur_max = max(p[i], cur_max + p[i]);
            max_sum = max(max_sum, cur_max);
            cur_min = min(p[i], cur_min + p[i]);
            min_sum = min(min_sum, cur_min);
            total += p[i];
        }
        
        if (total == min_sum) {
            cout << max_sum << "\n";
        } else {
            cout << max(max_sum, total - min_sum) << "\n";
        }
    }
    
    return 0;
}
