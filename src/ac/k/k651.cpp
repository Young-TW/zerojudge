#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    while (std::cin >> N) {
        std::vector<int> moves(N);
        for (int i = 0; i < N; ++i) std::cin >> moves[i];
        int Q;
        if (!(std::cin >> Q)) break;
        std::vector<int> queries(Q);
        int maxX = 0;
        for (int i = 0; i < Q; ++i) {
            std::cin >> queries[i];
            if (queries[i] > maxX) maxX = queries[i];
        }

        std::vector<char> win(maxX + 1, 0);   // 0 = lose, 1 = win
        win[0] = 0;
        for (int i = 1; i <= maxX; ++i) {
            bool w = false;
            for (int a : moves) {
                if (a <= i && !win[i - a]) {
                    w = true;
                    break;
                }
            }
            win[i] = w;
        }

        for (int x : queries) {
            if (win[x]) std::cout << "Win!\n";
            else        std::cout << "Lose\n";
        }
    }
    return 0;
}
