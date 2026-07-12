#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::vector<int> nuts;
    int n;
    while (std::cin >> n) {
        nuts.push_back(n);
    }
    
    std::sort(nuts.begin(), nuts.end());
    
    for (size_t i = 0; i < nuts.size(); ++i) {
        if (i > 0) {
            std::cout << " ";
        }
        std::cout << nuts[i];
    }
    std::cout << "\n";
    
    return 0;
}
