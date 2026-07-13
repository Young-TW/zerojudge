#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    while (cin >> N >> M) {
        if (N == 0 || M == 0) {
            cout << 0 << "\n";
            continue;
        }

        vector<vector<int>> A(N, vector<int>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> A[i][j];
            }
        }

        if (N < M) {
            vector<vector<int>> tmp(M, vector<int>(N));
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    tmp[j][i] = A[i][j];
                }
            }
            A = tmp;
            swap(N, M);
        }

        vector<vector<int>> R(N, vector<int>(M, 1));
        for (int i = 0; i < N; ++i) {
            for (int j = M - 2; j >= 0; --j) {
                if (A[i][j] < A[i][j + 1]) {
                    R[i][j] = R[i][j + 1] + 1;
                } else {
                    R[i][j] = 1;
                }
            }
        }

        vector<vector<int>> D(N, vector<int>(M, 1));
        for (int j = 0; j < M; ++j) {
            for (int i = N - 2; i >= 0; --i) {
                if (A[i][j] < A[i + 1][j]) {
                    D[i][j] = D[i + 1][j] + 1;
                } else {
                    D[i][j] = 1;
                }
            }
        }

        int max_area = 1;
        for (int c1 = 0; c1 < M; ++c1) {
            vector<int> min_D(N);
            for (int i = 0; i < N; ++i) {
                min_D[i] = D[i][c1];
            }
            for (int c2 = c1; c2 < M; ++c2) {
                int W = c2 - c1 + 1;
                for (int i = 0; i < N; ++i) {
                    if (D[i][c2] < min_D[i]) {
                        min_D[i] = D[i][c2];
                    }
                }
                
                int r = 0;
                while (r < N) {
                    if (R[r][c1] < W) {
                        r++;
                        continue;
                    }
                    int L = r;
                    while (r < N && R[r][c1] >= W) {
                        r++;
                    }
                    int R_bound = r - 1;
                    for (int r1 = L; r1 <= R_bound; ++r1) {
                        int max_r2 = r1 + min_D[r1] - 1;
                        if (max_r2 > R_bound) max_r2 = R_bound;
                        int H = max_r2 - r1 + 1;
                        if (W * H > max_area) {
                            max_area = W * H;
                        }
                    }
                }
            }
        }
        cout << max_area << "\n";
    }
    return 0;
}
