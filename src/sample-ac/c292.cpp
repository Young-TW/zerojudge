// https://zerojudge.tw/ShowProblem?problemid=c292
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, dir;
    std::cin >> n >> dir;

    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> a[i][j];

    // direction codes: 0=left, 1=up, 2=right, 3=down
    // clockwise turn (matching samples): dir = (dir + 1) % 4
    const int DR[4] = {0, -1, 0, 1};
    const int DC[4] = {-1, 0, 1, 0};

    int r = n / 2, c = n / 2;
    std::string out;
    out += char('0' + a[r][c]);

    int total = n * n;
    int visited = 1;
    int runLen = 1;
    int turnCount = 0;  // increment run length every two turns

    while (visited < total) {
        for (int step = 0; step < runLen && visited < total; ++step) {
            r += DR[dir];
            c += DC[dir];
            out += char('0' + a[r][c]);
            ++visited;
        }
        dir = (dir + 1) % 4;  // clockwise turn
        if (++turnCount % 2 == 0)
            ++runLen;
    }

    std::cout << out << '\n';
    return 0;
}
