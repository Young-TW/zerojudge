#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    while (std::cin >> N >> M) {
        // reach[i][j] == true  =>  i is stronger than j (path exists)
        std::vector<std::vector<char>> reach(N + 1, std::vector<char>(N + 1, 0));

        for (int k = 0; k < M; ++k) {
            int A, B;
            std::cin >> A >> B;
            reach[A][B] = 1;
        }

        // Floyd‑Warshall transitive closure
        for (int k = 1; k <= N; ++k) {
            for (int i = 1; i <= N; ++i) if (reach[i][k]) {
                for (int j = 1; j <= N; ++j) if (reach[k][j]) {
                    reach[i][j] = 1;
                }
            }
        }

        std::vector<int> ans;
        for (int i = 1; i <= N; ++i) {
            int cnt = 0;
            for (int j = 1; j <= N; ++j) if (i != j) {
                if (reach[i][j] || reach[j][i]) ++cnt;
            }
            if (cnt == N - 1) ans.push_back(i);
        }

        if (ans.empty()) {
            std::cout << "non\n";
        } else {
            for (size_t idx = 0; idx < ans.size(); ++idx) {
                if (idx) std::cout << ' ';
                std::cout << ans[idx];
            }
            std::cout << '\n';
        }
    }
    return 0;
}
