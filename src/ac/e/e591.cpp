#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    if (!(std::cin >> T)) return 0;
    while (T--) {
        int n;
        std::cin >> n;
        std::vector<long long> c(n);
        for (int i = 0; i < n; ++i) std::cin >> c[i];

        if (n == 1) {
            std::cout << 1 << '\n';
            continue;
        }

        long long sum = c[0];          // C1 is always kept
        int cnt = 1;                   // count of kept coins

        for (int i = 1; i < n - 1; ++i) {   // i corresponds to Ci+1 (0‑based)
            if (sum + c[i] < c[i + 1]) {
                ++cnt;
                sum += c[i];
            }
        }
        ++cnt;                         // Cn is always kept
        std::cout << cnt << '\n';
    }
    return 0;
}
