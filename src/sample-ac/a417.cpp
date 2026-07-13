#include <cstdio>
#include <cstring>

int mat[105][105];

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int N, M;
        scanf("%d %d", &N, &M);
        memset(mat, 0, sizeof(mat));
        int dr[4], dc[4];
        if (M == 1) {
            dr[0]=0;  dc[0]=1;
            dr[1]=1;  dc[1]=0;
            dr[2]=0;  dc[2]=-1;
            dr[3]=-1; dc[3]=0;
        } else {
            dr[0]=1;  dc[0]=0;
            dr[1]=0;  dc[1]=1;
            dr[2]=-1; dc[2]=0;
            dr[3]=0;  dc[3]=-1;
        }
        int r = 0, c = 0, dir = 0;
        for (int i = 1; i <= N*N; i++) {
            mat[r][c] = i;
            int nr = r + dr[dir], nc = c + dc[dir];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N || mat[nr][nc] != 0) {
                dir = (dir + 1) % 4;
                nr = r + dr[dir];
                nc = c + dc[dir];
            }
            r = nr; c = nc;
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%5d ", mat[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
