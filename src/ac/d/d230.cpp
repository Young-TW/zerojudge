#include <iostream>
#include <vector>

const int MOD = 10000000;
const int MAXN = 5000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Precompute a[n] for n = 0..MAXN
    std::vector<int> a(MAXN + 1, 0);
    std::vector<int> c2(MAXN + 1, 0);
    std::vector<int> c3(MAXN + 1, 0);

    a[0] = 0;
    a[1] = 1;

    for (int n = 2; n <= MAXN; ++n) {
        long long sum2 = 0;
        for (int i = 1; i <= n - 2; ++i) {
            sum2 += (long long)a[i] * a[n - 1 - i];
        }
        c2[n - 1] = sum2 % MOD;

        long long sum3 = 0;
        for (int i = 1; i <= n - 2; ++i) {
            sum3 += (long long)c2[i] * a[n - 1 - i];
        }
        c3[n - 1] = sum3 % MOD;

        long long val = (3LL * a[n - 1] + 3LL * c2[n - 1] + c3[n - 1]) % MOD;
        a[n] = (int)val;
    }

    int n;
    while (std::cin >> n) {
        if (n >= 0 && n <= MAXN) {
            std::cout << a[n] << "\n";
        }
    }

    return 0;
}
