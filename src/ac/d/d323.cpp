#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    while (std::cin >> N) {
        std::vector<int> nums(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> nums[i];
        }
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < N; ++i) {
            if (i != 0) {
                std::cout << ' ';
            }
            std::cout << nums[i];
        }
        std::cout << '\n';
    }

    return 0;
}
