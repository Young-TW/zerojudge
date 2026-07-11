#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    while (std::cin >> N) {
        std::vector<int> v(N);
        std::iota(v.begin(), v.end(), 1);
        
        do {
            for (int i = 0; i < N; ++i) {
                if (i > 0) std::cout << ' ';
                std::cout << v[i];
            }
            std::cout << '\n';
        } while (std::next_permutation(v.begin(), v.end()));
    }
    
    return 0;
}
