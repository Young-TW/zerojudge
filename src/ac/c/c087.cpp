#include <cstdio>
#include <cmath>

int gcd(int a, int b){
    while(b){ int t = a % b; a = b; b = t; }
    return a;
}

int main(){
    int N;
    while(scanf("%d", &N) == 1){
        if(N == 0) break;
        static int a[64];
        for(int i = 0; i < N; i++) scanf("%d", &a[i]);
        int total = N * (N - 1) / 2;
        int cop = 0;
        for(int i = 0; i < N; i++){
            for(int j = i + 1; j < N; j++){
                if(gcd(a[i], a[j]) == 1) cop++;
            }
        }
        if(cop == 0){
            printf("No estimate for this data set.\n");
        } else {
            double pi = sqrt(6.0 * (double)total / (double)cop);
            printf("%.6f\n", pi);
        }
    }
    return 0;
}
