#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    bool firstCase = true;
    int n;
    while (std::cin >> n) {
        if (n == 0) break;                 // end of all test cases

        // board[x][y] : first move number on (x,y), 0 = empty
        int board[20][20] = {0};

        // store all move numbers for each coordinate
        std::vector<int> steps[20][20];

        for (int i = 1; i <= n; ++i) {
            int x, y;
            std::cin >> x >> y;            // 1 .. 19
            steps[x][y].push_back(i);
            if (board[x][y] == 0) board[x][y] = i;
        }

        if (!firstCase) std::cout << "\n";
        firstCase = false;

        // print board: y = 19 .. 1, x = 1 .. 19
        for (int y = 19; y >= 1; --y) {
            for (int x = 1; x <= 19; ++x) {
                if (x > 1) std::cout << ' ';
                std::cout << board[x][y];
            }
            std::cout << "\n";
        }

        // collect duplicate information
        struct DupInfo {
            std::vector<int> v;   // all move numbers on this point
        };
        std::vector<DupInfo> dup;

        for (int x = 1; x <= 19; ++x)
            for (int y = 1; y <= 19; ++y)
                if (steps[x][y].size() >= 2)
                    dup.push_back({steps[x][y]});

        // sort by the first move number
        std::sort(dup.begin(), dup.end(),
                  [](const DupInfo& a, const DupInfo& b) {
                      return a.v[0] < b.v[0];
                  });

        // output duplicate lines
        for (const auto& d : dup) {
            for (size_t i = 0; i < d.v.size(); ++i) {
                if (i) std::cout << " = ";
                std::cout << d.v[i];
            }
            std::cout << "\n";
        }
    }
    return 0;
}
