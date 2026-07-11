#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> A(N, vector<int>(M));
        vector<vector<int>> B(N, vector<int>(M));
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> A[i][j];
            }
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> B[i][j];
            }
        }
        
        vector<int> row_sum(N, 0);
        vector<int> col_sum(M, 0);
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                row_sum[i] += B[i][j];
                col_sum[j] += B[i][j];
            }
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if ((row_sum[i] + col_sum[j] - B[i][j]) % 2 == 1) {
                    A[i][j] ^= 1;
                }
            }
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cout << A[i][j] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
