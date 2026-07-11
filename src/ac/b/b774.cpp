#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> A(N, vector<int>(M));
        vector<int> S(N);
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> A[i][j];
            }
            cin >> S[i];
        }

        vector<int> target(M);
        for (int j = 0; j < M; ++j) {
            cin >> target[j];
        }

        // 我們需要解線性方程組來找出每題的分數 x_j
        // sum(A[i][j] * x_j) = S[i]
        // 由於分數必須是非負實數，這是一個線性規劃問題或簡單的線性代數問題
        // 但因為 M 和 N 很小 (<=100)，我們可以嘗試用高斯消去法找出一組解，
        // 然後檢查是否有唯一解。
        
        // 更簡單的方法：因為我們只需要知道 target 的總分，
        // 我們可以將問題視為尋找 x_j 使得所有方程式成立。
        // 如果有矛盾 -> contradictory
        // 如果有多組解導致不同的 target 總分 -> not sure
        // 如果有唯一解 -> 輸出四捨五入的結果

        // 使用高斯消去法處理線性方程組
        // 增廣矩陣 [A | S]
        vector<vector<double>> mat(N, vector<double>(M + 1));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                mat[i][j] = static_cast<double>(A[i][j]);
            }
            mat[i][M] = static_cast<double>(S[i]);
        }

        int rank = 0;
        vector<int> pivot_col(M, -1); // 記錄每一行的主元列
        vector<int> row_used(N, 0);

        // 高斯消去
        for (int col = 0; col < M && rank < N; ++col) {
            // 尋找主元
            int pivot_row = -1;
            for (int row = rank; row < N; ++row) {
                if (!row_used[row] && abs(mat[row][col]) > 1e-9) {
                    pivot_row = row;
                    break;
                }
            }

            if (pivot_row == -1) continue;

            // 交換行
            swap(mat[rank], mat[pivot_row]);
            row_used[rank] = 1;
            pivot_col[col] = rank;

            // 歸一化
            double div = mat[rank][col];
            for (int j = col; j <= M; ++j) {
                mat[rank][j] /= div;
            }

            // 消去其他行
            for (int row = 0; row < N; ++row) {
                if (row != rank && abs(mat[row][col]) > 1e-9) {
                    double factor = mat[row][col];
                    for (int j = col; j <= M; ++j) {
                        mat[row][j] -= factor * mat[rank][j];
                    }
                }
            }

            rank++;
        }

        // 檢查矛盾
        bool contradictory = false;
        for (int i = 0; i < N; ++i) {
            bool all_zero = true;
            for (int j = 0; j < M; ++j) {
                if (abs(mat[i][j]) > 1e-9) {
                    all_zero = false;
                    break;
                }
            }
            if (all_zero && abs(mat[i][M]) > 1e-9) {
                contradictory = true;
                break;
            }
        }

        if (contradictory) {
            cout << "contradictory" << endl;
            continue;
        }

        // 現在檢查是否有唯一解
        // 如果有自由變數，則可能有多組解
        // 我們需要檢查 target 向量是否在解空間中有唯一的值
        
        // 構造解：將自由變數設為 0，求出特解
        vector<double> x(M, 0.0);
        vector<bool> is_free(M, true);
        
        for (int j = 0; j < M; ++j) {
            if (pivot_col[j] != -1) {
                is_free[j] = false;
                int row = pivot_col[j];
                x[j] = mat[row][M];
                for (int k = j + 1; k < M; ++k) {
                    x[j] -= mat[row][k] * x[k];
                }
            }
        }

        // 檢查非負約束（雖然題目沒明確說分數必須整數，但通常考試分數是非負的）
        // 實際上題目只說"配分"，應該是正數或零
        // 但根據範例，我們先不強制非負，只看線性方程組的解

        // 檢查是否唯一：如果有自由變數，且這些自由變數會影響 target 的總分
        // 則為 not sure
        
        // 計算當前的 target 總分
        double current_score = 0.0;
        for (int j = 0; j < M; ++j) {
            current_score += target[j] * x[j];
        }

        // 檢查是否有自由變數會影響結果
        // 對於每個自由變數，我們看它是否能改變 target 的總分
        bool not_sure = false;
        
        if (rank < M) {
            // 有自由變數，需要檢查是否影響 target
            // 構造齊次方程組的基礎解系
            // 對於每個自由變數，設為 1，其他自由變數設為 0，求解
            
            for (int free_var = 0; free_var < M; ++free_var) {
                if (!is_free[free_var]) continue;
                
                // 構造一個解：free_var = 1, 其他自由變數 = 0
                vector<double> delta_x(M, 0.0);
                delta_x[free_var] = 1.0;
                
                // 根據主元變數表達自由變數
                for (int j = 0; j < M; ++j) {
                    if (!is_free[j] && pivot_col[j] != -1) {
                        int row = pivot_col[j];
                        double val = 0.0;
                        for (int k = j + 1; k < M; ++k) {
                            if (is_free[k]) {
                                val -= mat[row][k] * delta_x[k];
                            }
                        }
                        delta_x[j] = val;
                    }
                }
                
                // 檢查這個方向是否會改變 target 的總分
                double delta_score = 0.0;
                for (int j = 0; j < M; ++j) {
                    delta_score += target[j] * delta_x[j];
                }
                
                if (abs(delta_score) > 1e-9) {
                    not_sure = true;
                    break;
                }
            }
        }

        if (not_sure) {
            cout << "not sure" << endl;
        } else {
            // 四捨五入到整數
            long long result = static_cast<long long>(floor(current_score + 0.5));
            cout << result << endl;
        }
    }

    return 0;
}
