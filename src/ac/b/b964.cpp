#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int people, temp;
    std::vector<int> value;
    std::cin >> people;
    for (int i = 0; i < people; i++) {
        std::cin >> temp;
        value.push_back(temp);
    }

    sort(value.begin(), value.end());
    for (auto i : value) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
    bool u = 1, d = 1;
    for (auto i : value) {
        if (i < 60) {
            u = 0;
        }

        if (i >= 60) {
            d = 0;
        }
    }

    auto l = lower_bound(value.begin(), value.end(), 60);
    if (u) {
        std::cout << "best case" << std::endl;
    } else {
        std::cout << *(l - 1) << std::endl;
    }

    if (d) {
        std::cout << "worst case" << std::endl;
    } else {
        auto l = lower_bound(value.begin(), value.end(), 60);
        std::cout << *l << std::endl;
    }

    return 0;
}