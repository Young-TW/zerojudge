#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n,m;
    std::vector<int> ar;

    while (std::cin >> n) {
        for (int i=0; i<n; i++) {
            std::cin >> m;
            ar.push_back(m);
        }

        std::sort(ar.begin(), ar.end());
        for (int i=0; i<n; i++) {
            std::cout << ar[i] << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}

// 明明愛排列