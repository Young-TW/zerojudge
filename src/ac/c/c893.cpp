#include <iostream>
#include <iomanip>
#include <vector>

int main() {
    int N, K;
    while (std::cin >> N >> K) {
        std::vector<int> C(K);
        long long sum_sq = 0;
        for (int i = 0; i < K; ++i) {
            std::cin >> C[i];
            sum_sq += static_cast<long long>(C[i]) * C[i];
        }

        double numerator = static_cast<double>(N) * N - static_cast<double>(sum_sq);
        double denominator = static_cast<double>(N);
        double ans = numerator / denominator;

        std::cout << std::fixed << std::setprecision(3) << ans << std::endl;
    }
    return 0;
}
