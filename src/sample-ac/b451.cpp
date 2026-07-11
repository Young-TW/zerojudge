#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int A_H, A_W, B_H, B_W;
    while (cin >> A_H >> A_W >> B_H >> B_W) {
        vector<vector<int>> A(A_H, vector<int>(A_W));
        vector<vector<int>> B(B_H, vector<int>(B_W));

        for (int i = 0; i < A_H; ++i) {
            for (int j = 0; j < A_W; ++j) {
                cin >> A[i][j];
            }
        }

        for (int i = 0; i < B_H; ++i) {
            for (int j = 0; j < B_W; ++j) {
                cin >> B[i][j];
            }
        }

        long long min_diff = LLONG_MAX;
        int best_x = 1, best_y = 1;

        for (int i = 0; i <= A_H - B_H; ++i) {
            for (int j = 0; j <= A_W - B_W; ++j) {
                long long diff = 0;
                for (int bi = 0; bi < B_H; ++bi) {
                    for (int bj = 0; bj < B_W; ++bj) {
                        int a_val = A[i + bi][j + bj];
                        int b_val = B[bi][bj];
                        diff += (a_val - b_val) * (a_val - b_val);
                        if (diff > min_diff) break;
                    }
                    if (diff > min_diff) break;
                }
                if (diff < min_diff) {
                    min_diff = diff;
                    best_x = i + 1;
                    best_y = j + 1;
                } else if (diff == min_diff) {
                    if (i + 1 < best_x) {
                        best_x = i + 1;
                        best_y = j + 1;
                    } else if (i + 1 == best_x && j + 1 < best_y) {
                        best_y = j + 1;
                    }
                }
            }
        }

        cout << best_x << " " << best_y << "\n";
    }

    return 0;
}
