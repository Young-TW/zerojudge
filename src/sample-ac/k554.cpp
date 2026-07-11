#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<vector<int>> grid(N, vector<int>(M));
        vector<vector<int>> risk(N, vector<int>(M, 0));
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> grid[i][j];
            }
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (grid[i][j] == 1) {
                    risk[i][j]++;
                    if (i > 0) risk[i-1][j]++;
                    if (i < N - 1) risk[i+1][j]++;
                    if (j > 0) risk[i][j-1]++;
                    if (j < M - 1) risk[i][j+1]++;
                } else if (grid[i][j] == 2) {
                    for (int k = 0; k < N; ++k) {
                        risk[k][j]++;
                    }
                    for (int k = 0; k < M; ++k) {
                        risk[i][k]++;
                    }
                    risk[i][j]--; // Subtract 1 because the center was incremented twice
                }
            }
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cout << risk[i][j];
                if (j < M - 1) {
                    cout << " ";
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
