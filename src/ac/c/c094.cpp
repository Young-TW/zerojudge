// c094 / UVa 661 - Blowing Fuses
// Self-written solution.
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n, m, c;
    int seq = 0;
    while (std::cin >> n >> m >> c) {
        if (n == 0 && m == 0 && c == 0) break;

        std::vector<long long> power(n + 1, 0);
        for (int i = 1; i <= n; ++i) std::cin >> power[i];

        std::vector<char> on(n + 1, 0);   // 0 = off, 1 = on
        long long cur = 0;                // current total consumption
        long long mx  = 0;                // maximal consumption seen
        bool blown = false;               // did we exceed the fuse?

        for (int i = 0; i < m; ++i) {
            int k; std::cin >> k;
            if (on[k]) {                  // turn off
                cur -= power[k];
                on[k] = 0;
            } else {                      // turn on
                cur += power[k];
                on[k] = 1;
            }
            if (cur > mx) mx = cur;
            if (cur > c) blown = true;
        }

        ++seq;
        if (seq > 1) std::cout << "\n";   // blank line BETWEEN sequences only
        std::cout << "Sequence " << seq << "\n";
        if (blown) {
            std::cout << "Fuse was blown.\n";
        } else {
            std::cout << "Fuse was not blown.\n";
            std::cout << "Maximal power consumption was " << mx << " amperes.\n";
        }
    }
    return 0;
}
