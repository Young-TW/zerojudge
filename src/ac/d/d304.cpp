#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    while (std::cin >> n) {
        // Factorize n into prime factors
        std::vector<int> prime_factors;
        int temp = n;
        for (int p = 2; p * p <= temp; ++p) {
            while (temp % p == 0) {
                prime_factors.push_back(p);
                temp /= p;
            }
        }
        if (temp > 1) prime_factors.push_back(temp);

        // Count prime factors
        int count2 = 0;
        std::map<int, int> odd_counts;
        for (int p : prime_factors) {
            if (p == 2) ++count2;
            else ++odd_counts[p];
        }

        // Minimum steps = sum of prime factors
        int min_steps = 0;
        for (int p : prime_factors) min_steps += p;

        // Generate all optimal factor sequences
        std::vector<std::vector<int>> all_seqs;
        for (int k = 0; k <= count2 / 2; ++k) {
            std::vector<int> base;
            // Remaining 2's
            for (int i = 0; i < count2 - 2 * k; ++i) base.push_back(2);
            // Odd primes (in increasing order)
            for (const auto& pr : odd_counts) {
                for (int i = 0; i < pr.second; ++i) base.push_back(pr.first);
            }
            // 4's from merged pairs of 2's
            for (int i = 0; i < k; ++i) base.push_back(4);

            std::sort(base.begin(), base.end());
            do {
                all_seqs.push_back(base);
            } while (std::next_permutation(base.begin(), base.end()));
        }

        // Sort all sequences lexicographically
        std::sort(all_seqs.begin(), all_seqs.end());

        // Output
        std::cout << "min : " << min_steps << "\n";
        std::cout << "way : " << all_seqs.size() << "\n";
        for (const auto& seq : all_seqs) {
            std::cout << "Ctrl C";
            for (size_t i = 0; i < seq.size(); ++i) {
                int f = seq[i];
                for (int j = 0; j < f - 1; ++j) {
                    std::cout << " + V";
                }
                if (i + 1 < seq.size()) {
                    std::cout << " + C";
                }
            }
            std::cout << "\n";
        }
    }
    return 0;
}
