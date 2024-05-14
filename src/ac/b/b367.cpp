#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, x, y, reg;
    std::vector<int> ar, revar;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        for (int j = 0; j < x * y; j++) {
            std::cin >> reg;
            ar.push_back(reg);
        }
        revar = ar;
        reverse(revar.begin(), revar.end());
        if (revar == ar) {
            std::cout << "go forward" << std::endl;
        } else {
            std::cout << "keep defending" << std::endl;
        }
        ar.clear();
    }
    return 0;
}