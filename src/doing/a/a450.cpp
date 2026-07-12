#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    static char inbuf[1 << 20];
    static char outbuf[1 << 20];
    setvbuf(stdin, inbuf, _IOFBF, sizeof(inbuf));
    setvbuf(stdout, outbuf, _IOFBF, sizeof(outbuf));
    
    int N, Q;
    while (scanf("%d %d", &N, &Q) == 2) {
        int* A = new int[N];
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
        sort(A, A + N);
        
        for (int q = 0; q < Q; q++) {
            int a, b;
            scanf("%d %d", &a, &b);
            int* lo = lower_bound(A, A + N, a);
            int* hi = upper_bound(A, A + N, b);
            int cnt = hi - lo;
            if (cnt == 0) {
                printf("The candies are too short // 找不到身高介於 %d - %d 之間的\n", a, b);
            } else {
                printf("%d  // 身高介於  %d - %d 的有", cnt, a, b);
                for (int* p = lo; p < hi; p++) {
                    printf(" %d", *p);
                }
                printf("\n");
            }
        }
        delete[] A;
    }
    return 0;
}
