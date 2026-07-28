// i762. 大排序 — n(<=5e7) 個 u32,用題目 ideone 提供的生成/輸出函式。
// 生成:xorshift32 (x^=x<<13; x^=x>>17; x^=x<<5),seed 逐步演進填 a[i]。
// 輸出:非印全部,而是雜湊 re=n; x=23333333; 對「排序後」每個 a[i]: re^=(a[i]+x); x 再 xorshift。
// 排序用 LSD 基數排序(4×8bit,O(n),~0.5s)避免 std::sort 在 5e7 觸 3.0s TLE。
#include <cstdio>
using u32=unsigned int;
static u32 a[50000000];
static u32 b[50000000];
int main(){
    int n; u32 seed;
    if(scanf("%d %u",&n,&seed)!=2) return 0;
    for(int i=0;i<n;i++){ seed^=seed<<13; seed^=seed>>17; seed^=seed<<5; a[i]=seed; }
    u32 *src=a, *dst=b;
    for(int sh=0; sh<32; sh+=8){
        u32 cnt[256]={0};
        for(int i=0;i<n;i++) cnt[(src[i]>>sh)&0xFF]++;
        u32 pos=0;
        for(int c=0;c<256;c++){ u32 t=cnt[c]; cnt[c]=pos; pos+=t; }
        for(int i=0;i<n;i++){ u32 v=src[i]; dst[cnt[(v>>sh)&0xFF]++]=v; }
        u32* tmp=src; src=dst; dst=tmp;
    }
    u32 re=(u32)n, x=23333333u;
    for(int i=0;i<n;i++){ re^=(src[i]+x); x^=x<<13; x^=x>>17; x^=x<<5; }
    printf("%u\n",re);
    return 0;
}
