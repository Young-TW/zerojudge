#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int* count = (int*)calloc(1000001, sizeof(int));
    int max_flavor = 0;
    for (int i = 0; i < N; i++) {
        int flavor;
        scanf("%d", &flavor);
        count[flavor]++;
        if (flavor > max_flavor) {
            max_flavor = flavor;
        }
    }
    for (int i = 1; i <= max_flavor; i++) {
        if (count[i] % 2 != 0) {
            printf("%d\n", i);
            break;
        }
    }
    free(count);
    return 0;
}
