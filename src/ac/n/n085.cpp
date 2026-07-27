#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    while (std::cin >> N) {
        std::vector<long long> t(N), TA(N), TB(N), finishA(N);
        for (int i = 0; i < N; ++i) {
            long long m, n;
            std::cin >> t[i] >> m >> n;
            long long area = m * n;
            TA[i] = area / 2;          // floor
            TB[i] = area;
        }

        long long curA = 0;
        for (int i = 0; i < N; ++i) {
            long long startA = std::max(t[i], curA);
            finishA[i] = startA + TA[i];
            curA = finishA[i];
        }

        long long curB = 0;
        std::size_t idx = 0;
        std::vector<long long> stk;   // acts as a stack, stores TB values

        while (idx < static_cast<std::size_t>(N) || !stk.empty()) {
            if (stk.empty()) {
                curB = std::max(curB, finishA[idx]);
            }
            while (idx < static_cast<std::size_t>(N) && finishA[idx] <= curB) {
                stk.push_back(TB[idx]);
                ++idx;
            }
            long long job = stk.back();
            stk.pop_back();
            curB += job;
        }

        std::cout << curB << '\n';
    }
    return 0;
}
