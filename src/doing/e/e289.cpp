#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int m, n;
    while (scanf("%d %d", &m, &n) == 2) {
        vector<int> colors(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &colors[i]);
        }
        
        vector<int> sorted_colors = colors;
        sort(sorted_colors.begin(), sorted_colors.end());
        sorted_colors.erase(unique(sorted_colors.begin(), sorted_colors.end()), sorted_colors.end());
        
        int num_unique = sorted_colors.size();
        vector<int> cnt(num_unique, 0);
        vector<int> idx(n);
        for (int i = 0; i < n; ++i) {
            idx[i] = lower_bound(sorted_colors.begin(), sorted_colors.end(), colors[i]) - sorted_colors.begin();
        }
        
        int distinct = 0;
        long long ans = 0;
        
        for (int i = 0; i < n; ++i) {
            if (cnt[idx[i]] == 0) {
                distinct++;
            }
            cnt[idx[i]]++;
            
            if (i >= m) {
                cnt[idx[i - m]]--;
                if (cnt[idx[i - m]] == 0) {
                    distinct--;
                }
            }
            
            if (i >= m - 1) {
                if (distinct == m) {
                    ans++;
                }
            }
        }
        
        printf("%lld\n", ans);
    }
    
    return 0;
}
