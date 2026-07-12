#include <iostream>
#include <vector>
#include <algorithm>

const int MAX_PRIME = 46340; // sqrt(2147483647)
const int BLOCK_SIZE = 1000000;
const int GLOBAL_MAX_NUM = 2095133040;
const int GLOBAL_MAX_DIV = 1600;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Precompute primes up to MAX_PRIME
    std::vector<int> primes;
    std::vector<bool> is_composite(MAX_PRIME + 1, false);
    for (int i = 2; i <= MAX_PRIME; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            if (1LL * i * i <= MAX_PRIME) {
                for (int j = i * i; j <= MAX_PRIME; j += i) {
                    is_composite[j] = true;
                }
            }
        }
    }

    int N;
    if (!(std::cin >> N)) return 0;
    for (int caseNum = 0; caseNum < N; ++caseNum) {
        int L, U;
        std::cin >> L >> U;

        // If the range contains the globally optimal number, answer immediately.
        if (L <= GLOBAL_MAX_NUM && GLOBAL_MAX_NUM <= U) {
            std::cout << "Between " << L << " and " << U << ", "
                      << GLOBAL_MAX_NUM << " has a maximum of "
                      << GLOBAL_MAX_DIV << " divisors.\n";
            continue;
        }

        int best_num = L;
        int best_div = 0;

        // Process the range in blocks to keep memory usage low.
        for (long long block_start = L; block_start <= U; block_start += BLOCK_SIZE) {
            long long block_end = std::min<long long>(U, block_start + BLOCK_SIZE - 1);
            int block_len = static_cast<int>(block_end - block_start + 1);

            std::vector<int> val(block_len);
            std::vector<int> div_count(block_len, 1);
            for (int i = 0; i < block_len; ++i) {
                val[i] = static_cast<int>(block_start + i);
            }

            for (int p : primes) {
                if (1LL * p * p > block_end) break;
                long long start = (block_start + p - 1) / p * 1LL * p;
                for (long long j = start; j <= block_end; j += p) {
                    int idx = static_cast<int>(j - block_start);
                    int cnt = 0;
                    while (val[idx] % p == 0) {
                        val[idx] /= p;
                        ++cnt;
                    }
                    div_count[idx] *= (cnt + 1);
                }
            }

            for (int i = 0; i < block_len; ++i) {
                if (val[i] > 1) {
                    div_count[i] *= 2;
                }
                if (div_count[i] > best_div) {
                    best_div = div_count[i];
                    best_num = static_cast<int>(block_start + i);
                }
            }
        }

        std::cout << "Between " << L << " and " << U << ", "
                  << best_num << " has a maximum of "
                  << best_div << " divisors.\n";
    }
    return 0;
}
