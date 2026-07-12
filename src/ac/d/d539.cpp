#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
        
        int LOG = 1;
        while ((1 << LOG) <= n) {
            LOG++;
        }
        
        std::vector<std::vector<int>> st(LOG, std::vector<int>(n));
        for (int i = 0; i < n; ++i) {
            st[0][i] = arr[i];
        }
        
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = std::max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
        
        std::vector<int> lg2(n + 1);
        if (n >= 1) lg2[1] = 0;
        for (int i = 2; i <= n; ++i) {
            lg2[i] = lg2[i / 2] + 1;
        }
        
        int m;
        std::cin >> m;
        while (m--) {
            int a, b;
            std::cin >> a >> b;
            if (a > b) std::swap(a, b);
            a--; b--;
            int k = lg2[b - a + 1];
            std::cout << std::max(st[k][a], st[k][b - (1 << k) + 1]) << '\n';
        }
    }
    
    return 0;
}
