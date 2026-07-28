#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const int MAX_N = 45;                 // enough for the problem limits
    std::vector<long long> a(MAX_N + 1);
    a[1] = 1;
    a[2] = 3;
    for (int i = 3; i <= MAX_N; ++i) {
        a[i] = a[i - 1] + a[i - 2];
    }

    int n;
    while (std::cin >> n) {
        std::cout << a[n] << '\n';
    }
    return 0;
}
