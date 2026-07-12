#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long n;
    while (std::cin >> n) {
        std::vector<long long> a(n);
        for (long long &x : a) std::cin >> x;
        std::sort(a.begin(), a.end(), std::greater<long long>());

        long long cum = 0;   // 已選取元素的累積和
        long long tot = 0;   // 累積的前綴和之和

        for (long long v : a) {
            if (cum + 2 * v > 0) {
                cum += v;
                tot += cum;
            } else {
                break;
            }
        }
        long long ans = tot + cum;
        std::cout << ans << '\n';
    }
    return 0;
}
