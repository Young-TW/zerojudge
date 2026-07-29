#include <cstdio>
int main(){
    // Pell: x^2 - 8 y^2 = 1, x=2n+1, y=k. Fundamental (3,1). Skip trivial (1,1).
    long long x=3,y=1;
    for(int i=0;i<10;i++){
        long long nx=3*x+8*y, ny=x+3*y;
        x=nx; y=ny;
        long long n=(x-1)/2, k=y;
        printf("%10lld%10lld\n", k, n);
    }
    return 0;
}
