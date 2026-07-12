#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    if (!(std::cin >> t)) return 0;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i) std::cin >> a[i];
        
        unsigned int total = 1u << n;
        long long sum = 0;
        long long ans = 0;
        ans ^= sum; // empty subset
        
        unsigned int prev_gray = 0;
        for (unsigned int i = 1; i < total; ++i) {
            unsigned int gray = i ^ (i >> 1);
            unsigned int diff = gray ^ prev_gray;
            int bit = __builtin_ctz(diff);
            if (gray & diff) sum += a[bit];
            else sum -= a[bit];
            ans ^= sum;
            prev_gray = gray;
        }
        std::cout << ans << '\n';
    }
    return 0;
}
