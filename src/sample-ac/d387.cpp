#include <iostream>

const int MAXN = 1000005;
bool is_prime[MAXN];

int reverse_num(int n) {
    int rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (int i = 0; i < MAXN; ++i) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAXN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int N;
    while (std::cin >> N) {
        if (!is_prime[N]) {
            std::cout << N << " is not prime.\n";
        } else {
            int revN = reverse_num(N);
            if (revN != N && is_prime[revN]) {
                std::cout << N << " is emirp.\n";
            } else {
                std::cout << N << " is prime.\n";
            }
        }
    }

    return 0;
}
