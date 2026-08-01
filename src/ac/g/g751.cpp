#include <cstdio>
int main(){
    unsigned long long x=88172645463325252ULL;
    for(int i=0;i<2000;i++){ x^=x<<13; x^=x>>7; x^=x<<17; putchar(33+(x%94)); }
    return 0;
}
