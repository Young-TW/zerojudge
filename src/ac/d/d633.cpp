#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    long long r, m;
    const double pi = 2.0 * acos(0.0);
    
    while (std::cin >> r >> m) {
        // 根據範例反推，正確的圓心角應為 2π/(m+1)
        // 半徑序列: r, r*(m-1)/m, ..., r*1/m
        // 半徑總和 = r * (1 + (m-1)/m + ... + 1/m) = r * (m+1)/2
        // 單邊弧長總和 = 半徑總和 * 圓心角 = r*(m+1)/2 * 2π/(m+1) = π*r
        // 兩邊總長 = 2 * π * r
        double total_length = 2.0 * pi * static_cast<double>(r);
        
        std::cout << std::fixed << std::setprecision(5) << total_length << std::endl;
    }
    
    return 0;
}
