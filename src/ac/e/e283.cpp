#include <iostream>
#include <vector>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 4‑dimensional lookup table: tbl[b0][b1][b2][b3] = original character
    char tbl[2][2][2][2];
    // initialise all entries to '?' (should never be used)
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                for (int l = 0; l < 2; ++l)
                    tbl[i][j][k][l] = '?';

    // fill according to the problem statement
    tbl[0][1][0][1] = 'A';
    tbl[0][1][1][1] = 'B';
    tbl[0][0][1][0] = 'C';
    tbl[1][1][0][1] = 'D';
    tbl[1][0][0][0] = 'E';
    tbl[1][1][0][0] = 'F';

    int N;
    while (std::cin >> N) {
        std::string ans;
        ans.reserve(N);
        for (int i = 0; i < N; ++i) {
            int b0, b1, b2, b3;
            std::cin >> b0 >> b1 >> b2 >> b3;
            ans.push_back(tbl[b0][b1][b2][b3]);
        }
        std::cout << ans << '\n';
    }
    return 0;
}
