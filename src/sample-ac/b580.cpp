#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            int matrix[105][105];
            int r = N / 2, c = N / 2;
            int val = 1;
            matrix[r][c] = val++;
            
            int step = 1;
            int dir = 0; // 0:右, 1:上, 2:左, 3:下
            int dr[] = {0, -1, 0, 1};
            int dc[] = {1, 0, -1, 0};
            
            while (val <= N * N) {
                for (int i = 0; i < step; ++i) {
                    r += dr[dir];
                    c += dc[dir];
                    if (r >= 0 && r < N && c >= 0 && c < N) {
                        matrix[r][c] = val++;
                    }
                }
                if (dir % 2 == 1) {
                    step++;
                }
                dir = (dir + 1) % 4;
            }
            
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << setw(4) << matrix[i][j];
                    if (j < N - 1) {
                        cout << " ";
                    }
                }
                cout << "\n";
            }
        }
    }
    
    return 0;
}
