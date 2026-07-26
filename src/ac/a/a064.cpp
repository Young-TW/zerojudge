#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::vector<long long> answers;
    while (std::cin >> N) {
        std::vector<int> S(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> S[i];
        }
        
        std::vector<long long> lhs;
        lhs.reserve(static_cast<std::size_t>(N) * N * N);
        for (int a : S) {
            for (int b : S) {
                long long ab = static_cast<long long>(a) * b;
                for (int c : S) {
                    lhs.push_back(ab + c);
                }
            }
        }
        std::sort(lhs.begin(), lhs.end());
        
        long long ans = 0;
        for (int d : S) {
            if (d == 0) continue;
            for (int e : S) {
                for (int f : S) {
                    long long val = static_cast<long long>(d) * (static_cast<long long>(e) + f);
                    auto range = std::equal_range(lhs.begin(), lhs.end(), val);
                    ans += (range.second - range.first);
                }
            }
        }
        answers.push_back(ans);
    }
    
    for (std::size_t i = 0; i < answers.size(); ++i) {
        if (i > 0) std::cout << "\n\n";
        std::cout << answers[i];
    }
    std::cout << "\n";
    
    return 0;
}
