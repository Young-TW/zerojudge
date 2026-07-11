#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        long long A[3][3], C[3][3];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> A[i][j];
        cin >> s;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> C[i][j];
        
        long long cof[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int rows[2], cols[2];
                int ri = 0, ci = 0;
                for (int r = 0; r < 3; r++) if (r != i) rows[ri++] = r;
                for (int c = 0; c < 3; c++) if (c != j) cols[ci++] = c;
                long long m = A[rows[0]][cols[0]] * A[rows[1]][cols[1]] - A[rows[0]][cols[1]] * A[rows[1]][cols[0]];
                cof[i][j] = ((i + j) % 2 == 0) ? m : -m;
            }
        }
        
        long long det = 0;
        for (int j = 0; j < 3; j++) det += A[0][j] * cof[0][j];
        
        printf("B:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                long long n = 0;
                for (int k = 0; k < 3; k++) {
                    n += cof[k][i] * C[k][j];
                }
                long long d = det;
                if (d < 0) { n = -n; d = -d; }
                long long scaled = n * 10000;
                long long q = scaled / d;
                long long r = scaled % d;
                long long ar = r < 0 ? -r : r;
                if (2 * ar >= d) {
                    if (scaled >= 0) q++;
                    else q--;
                }
                long long ip = q / 10000;
                long long fp = q % 10000;
                if (fp < 0) fp = -fp;
                if (q < 0 && ip == 0) {
                    printf("-%lld.%04lld", ip, fp);
                } else {
                    printf("%lld.%04lld", ip, fp);
                }
                if (j < 2) printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}
