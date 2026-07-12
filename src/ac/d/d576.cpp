#include <iostream>
#include <vector>
#include <cstdint>

struct Result {
    long long winA;
    long long winB;
    long long draw;
};

int N;
int board[4][4];

Result dfs(int mask, int player, int lineType, int lineIndex, long long scoreA, long long scoreB) {
    // Check if there is any available cell in the required line.
    bool hasMove = false;
    if (lineType == 0) { // row
        for (int col = 1; col <= N; ++col) {
            int idx = (lineIndex - 1) * N + (col - 1);
            if ((mask & (1 << idx)) == 0) {
                hasMove = true;
                break;
            }
        }
    } else { // column
        for (int row = 1; row <= N; ++row) {
            int idx = (row - 1) * N + (lineIndex - 1);
            if ((mask & (1 << idx)) == 0) {
                hasMove = true;
                break;
            }
        }
    }

    if (!hasMove) {
        Result res = {0, 0, 0};
        if (scoreA > scoreB) res.winA = 1;
        else if (scoreA < scoreB) res.winB = 1;
        else res.draw = 1;
        return res;
    }

    Result res = {0, 0, 0};
    if (lineType == 0) { // row
        for (int col = 1; col <= N; ++col) {
            int idx = (lineIndex - 1) * N + (col - 1);
            if ((mask & (1 << idx)) == 0) {
                int r = lineIndex;
                int c = col;
                int newMask = mask | (1 << idx);
                long long newScoreA = scoreA, newScoreB = scoreB;
                if (player == 0) newScoreA += board[r - 1][c - 1];
                else newScoreB += board[r - 1][c - 1];
                int nextPlayer = 1 - player;
                int nextLineType = 1; // column
                int nextLineIndex = c;
                Result sub = dfs(newMask, nextPlayer, nextLineType, nextLineIndex, newScoreA, newScoreB);
                res.winA += sub.winA;
                res.winB += sub.winB;
                res.draw += sub.draw;
            }
        }
    } else { // column
        for (int row = 1; row <= N; ++row) {
            int idx = (row - 1) * N + (lineIndex - 1);
            if ((mask & (1 << idx)) == 0) {
                int r = row;
                int c = lineIndex;
                int newMask = mask | (1 << idx);
                long long newScoreA = scoreA, newScoreB = scoreB;
                if (player == 0) newScoreA += board[r - 1][c - 1];
                else newScoreB += board[r - 1][c - 1];
                int nextPlayer = 1 - player;
                int nextLineType = 0; // row
                int nextLineIndex = r;
                Result sub = dfs(newMask, nextPlayer, nextLineType, nextLineIndex, newScoreA, newScoreB);
                res.winA += sub.winA;
                res.winB += sub.winB;
                res.draw += sub.draw;
            }
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    while (std::cin >> N) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                std::cin >> board[i][j];
            }
        }
        Result ans = dfs(0, 0, 0, 1, 0, 0);
        std::cout << ans.winA << " " << ans.winB << " " << ans.draw << "\n";
    }
    return 0;
}
