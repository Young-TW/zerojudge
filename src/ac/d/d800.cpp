#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        vector<vector<int>> mat(N + 1, vector<int>(M + 1, 0));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                scanf("%d", &mat[i][j]);
            }
        }
        
        int logN = 0;
        while ((1 << (logN + 1)) <= N) ++logN;
        int logM = 0;
        while ((1 << (logM + 1)) <= M) ++logM;
        
        vector<vector<vector<vector<int>>>> st(
            logN + 1, vector<vector<vector<int>>>(
                logM + 1, vector<vector<int>>(
                    N + 1, vector<int>(M + 1, 0)
                )
            )
        );
        
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                st[0][0][i][j] = mat[i][j];
            }
        }
        
        for (int k = 1; k <= logN; ++k) {
            int half = 1 << (k - 1);
            for (int i = 1; i + (1 << k) - 1 <= N; ++i) {
                for (int j = 1; j <= M; ++j) {
                    st[k][0][i][j] = max(st[k-1][0][i][j], st[k-1][0][i+half][j]);
                }
            }
        }
        
        for (int l = 1; l <= logM; ++l) {
            int half = 1 << (l - 1);
            for (int i = 1; i <= N; ++i) {
                for (int j = 1; j + (1 << l) - 1 <= M; ++j) {
                    st[0][l][i][j] = max(st[0][l-1][i][j], st[0][l-1][i][j+half]);
                }
            }
        }
        
        for (int k = 1; k <= logN; ++k) {
            int half_k = 1 << (k - 1);
            for (int l = 1; l <= logM; ++l) {
                int half_l = 1 << (l - 1);
                for (int i = 1; i + (1 << k) - 1 <= N; ++i) {
                    for (int j = 1; j + (1 << l) - 1 <= M; ++j) {
                        st[k][l][i][j] = max(
                            max(st[k-1][l-1][i][j], st[k-1][l-1][i+half_k][j]),
                            max(st[k-1][l-1][i][j+half_l], st[k-1][l-1][i+half_k][j+half_l])
                        );
                    }
                }
            }
        }
        
        int Q;
        scanf("%d", &Q);
        while (Q--) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            
            int k = 0;
            while ((1 << (k + 1)) <= x2 - x1 + 1) ++k;
            int l = 0;
            while ((1 << (l + 1)) <= y2 - y1 + 1) ++l;
            
            int ans = max(
                max(st[k][l][x1][y1], st[k][l][x2 - (1 << k) + 1][y1]),
                max(st[k][l][x1][y2 - (1 << l) + 1], st[k][l][x2 - (1 << k) + 1][y2 - (1 << l) + 1])
            );
            
            printf("%d\n", ans);
        }
    }
    return 0;
}
