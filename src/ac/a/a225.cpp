#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::vector<int> ar;

    while (std::cin >> n) {
        ar.clear();
        for (int i = 0; i < n; i++) {
            std::cin >> m;
            ar.push_back(m);
        }

        std::stable_sort(ar.begin(), ar.end(), [](int a, int b) {
            int da = a % 10, db = b % 10;
            if (da != db) return da < db;
            return a > b;
        });

        for (int i = 0; i < n; i++) {
            std::cout << ar[i];
            if (i + 1 < n) std::cout << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}

// 明明愛排列
