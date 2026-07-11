#include <iostream>
#include <vector>
#include <utility>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int MAXN = 20000005;
    std::vector<char> is_prime(MAXN, 1);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i < MAXN; ++i) {
        if (is_prime[i]) {
            if (i == 2) {
                for (int j = i * i; j < MAXN; j += i) {
                    is_prime[j] = 0;
                }
            } else {
                for (int j = i * i; j < MAXN; j += i * 2) {
                    is_prime[j] = 0;
                }
            }
        }
    }

    std::vector<std::pair<int, int>> twin_primes;
    for (int i = 3; i < MAXN - 2; ++i) {
        if (is_prime[i] && is_prime[i + 2]) {
            twin_primes.push_back({i, i + 2});
            if (twin_primes.size() == 100000) break;
        }
    }

    int S;
    while (std::cin >> S) {
        std::cout << "(" << twin_primes[S - 1].first << ", " << twin_primes[S - 1].second << ")\n";
    }

    return 0;
}
