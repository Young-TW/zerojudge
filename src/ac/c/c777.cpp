#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const unsigned long long LIMIT = 1000000000000000000ULL; // 1e18

    // pre‑compute Tribonacci numbers up to LIMIT
    std::vector<unsigned long long> seq;
    seq.push_back(1);
    seq.push_back(2);
    seq.push_back(3);
    while (true) {
        __int128 nxt = (__int128)seq[seq.size() - 1] +
                      (__int128)seq[seq.size() - 2] +
                      (__int128)seq[seq.size() - 3];
        if (nxt > LIMIT) break;
        seq.push_back(static_cast<unsigned long long>(nxt));
    }

    unsigned long long n, m;
    while (std::cin >> n >> m) {
        if (n > m) {
            std::cout << 0 << '\n';
            continue;
        }
        auto itL = std::lower_bound(seq.begin(), seq.end(), n);
        auto itR = std::upper_bound(seq.begin(), seq.end(), m);
        std::cout << (itR - itL) << '\n';
    }
    return 0;
}
