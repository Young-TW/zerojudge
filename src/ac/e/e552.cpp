#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int MAX_N = 10000;
    std::vector<bool> is_prime(MAX_N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= MAX_N; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= MAX_N; i += p) {
                is_prime[i] = false;
            }
        }
    }

    std::vector<int> primes;
    for (int p = 2; p <= MAX_N; ++p) {
        if (is_prime[p]) {
            primes.push_back(p);
        }
    }

    std::vector<int> ans(MAX_N + 1, 0);
    int P = primes.size();
    for (int i = 0; i < P; ++i) {
        int sum = 0;
        for (int j = i; j < P; ++j) {
            sum += primes[j];
            if (sum > MAX_N) break;
            ans[sum]++;
        }
    }

    int n;
    while (std::cin >> n && n != 0) {
        std::cout << ans[n] << "\n";
    }

    return 0;
}
