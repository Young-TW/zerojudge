#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, reg;
    std::vector<int> v;
    while (std::cin >> n) {
        for (int i = 0; i < n; i++) {
            std::cin >> reg;
            v.push_back(reg);
        }

        sort(v.begin(), v.end());
        for (int i = 0; i < n; i++) {
            std::cout << v[i] << " ";
        }

        std::cout << std::endl;
        v.clear();
    }

    return 0;
}