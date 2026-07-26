#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Runner {
    int id;
    double time;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    while (std::cin >> N) {
        std::vector<Runner> runners(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> runners[i].id >> runners[i].time;
        }

        // 1. sort by time (ascending)
        std::sort(runners.begin(), runners.end(),
                  [](const Runner& a, const Runner& b) {
                      return a.time < b.time;
                  });

        int G = N / 8;                     // number of groups
        std::vector<std::vector<int>> groups(G);   // ids per group, in performance order

        // 2. S‑shaped group assignment
        int period = 2 * G;
        for (int i = 0; i < N; ++i) {
            int pos = i % period;
            int g;
            if (pos < G) g = pos;
            else        g = period - pos - 1;
            groups[g].push_back(runners[i].id);
        }

        // lane priority: 4,5,3,6,2,7,1,8  (0‑based indices)
        const int laneOrder[8] = {3, 4, 2, 5, 1, 6, 0, 7};

        // 3. output each group
        for (int g = 0; g < G; ++g) {
            int lane[8];
            for (int j = 0; j < 8; ++j) {
                lane[laneOrder[j]] = groups[g][j];
            }
            std::cout << (g + 1);
            for (int j = 0; j < 8; ++j) {
                std::cout << ' ' << lane[j];
            }
            std::cout << '\n';
        }
    }
    return 0;
}
