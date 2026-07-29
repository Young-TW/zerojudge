#include <cstdio>
static bool has9(long long x){ while(x){ if(x%10==9) return true; x/=10;} return false; }
int main(){
    // Longest, minimal-difference arithmetic sequence: first term 1, d=125, 72 terms (all 9-free).
    for(long long t=1; !has9(t); t+=125) printf("%lld\n", t);
    return 0;
}
