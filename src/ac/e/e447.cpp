#include <iostream>
#include <queue>

int main() {
    std::queue<int> nums;
    int n, k, x;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> k;
        switch (k) {
            case 1:
                std::cin >> x;
                nums.push(x);
                break;
            case 2:
                if (nums.empty())
                    std::cout << "-1" << std::endl;
                else
                    std::cout << nums.front() << std::endl;
                break;
            case 3:
                if (nums.empty())
                    break;
                else
                    nums.pop();
                break;
        }
    }
    return 0;
}