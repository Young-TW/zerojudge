#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

// reverse the order of rows (FLIP is self-inverse)
Matrix flip(const Matrix &m) {
    return Matrix(m.rbegin(), m.rend());
}

// rotate 90 degrees counter-clockwise (inverse of clockwise rotation)
Matrix rotateCCW(const Matrix &m) {
    int rows = m.size();
    int cols = m[0].size();
    Matrix r(cols, std::vector<int>(rows));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            r[cols - 1 - j][i] = m[i][j];
    return r;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int R, C, M;
    // multiple test cases until EOF (same judge family as b266)
    while (std::cin >> R >> C >> M) {
        Matrix b(R, std::vector<int>(C));
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                std::cin >> b[i][j];

        std::vector<int> ops(M);
        for (int k = 0; k < M; ++k)
            std::cin >> ops[k];

        // undo: apply inverse operations in reverse order
        for (int k = M - 1; k >= 0; --k) {
            if (ops[k] == 1)
                b = flip(b);
            else
                b = rotateCCW(b);
        }

        int nr = b.size();
        int nc = b[0].size();
        std::cout << nr << ' ' << nc << '\n';
        for (int i = 0; i < nr; ++i) {
            for (int j = 0; j < nc; ++j) {
                if (j) std::cout << ' ';
                std::cout << b[i][j];
            }
            std::cout << '\n';
        }
    }

    return 0;
}

// APCS 201603-2 矩陣轉換
