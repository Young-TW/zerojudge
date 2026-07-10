#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

// flip: reverse the order of rows (self-inverse)
Matrix flip(const Matrix &m) {
    return Matrix(m.rbegin(), m.rend());
}

// counter-clockwise 90 rotation (inverse of clockwise rotation)
Matrix rotateCCW(const Matrix &m) {
    int r = m.size();
    int c = m[0].size();
    Matrix res(c, std::vector<int>(r));
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j) {
            res[i][j] = m[j][c - 1 - i];
        }
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int R, C, M;
    // multiple test cases until EOF
    while (std::cin >> R >> C >> M) {
        Matrix mat(R, std::vector<int>(C));
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                std::cin >> mat[i][j];
            }
        }

        std::vector<int> ops(M);
        for (int k = 0; k < M; ++k) {
            std::cin >> ops[k];
        }

        // undo operations: reverse order, apply the inverse of each
        for (int k = M - 1; k >= 0; --k) {
            if (ops[k] == 1) {
                mat = flip(mat);
            } else {
                mat = rotateCCW(mat);
            }
        }

        int rr = mat.size();
        int cc = mat[0].size();
        std::cout << rr << ' ' << cc << '\n';
        for (int i = 0; i < rr; ++i) {
            for (int j = 0; j < cc; ++j) {
                if (j) {
                    std::cout << ' ';
                }
                std::cout << mat[i][j];
            }
            std::cout << '\n';
        }
    }

    return 0;
}

// 矩陣翻轉
