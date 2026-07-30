// d923 規律 — 自寫
// 自相似(風車)螺旋填數:大方框分四區,群組順序 TL,BR,BL,TR,每區遞迴同樣式。
// 令 x=I-1,y=J-1(0-based)。value = 1 + Σ_i (P(xbit_i,ybit_i)-1)*4^i
// 其中 P-1: (0,0)=0,(1,0)=3,(0,1)=2,(1,1)=1。
// 由樣本 (I=2,J=3)=12 推得並以獨立暴力(遞迴建格)全格驗證。
// I,J<=2^30 => value<=4^30=1152921504606846976 < 9.2e18,long long 安全。
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long I, J;
    while (cin >> I >> J){
        long long x = I - 1, y = J - 1;
        long long val = 1, pw = 1;
        while (x > 0 || y > 0){
            int xb = (int)(x & 1), yb = (int)(y & 1);
            int p;
            if (xb == 0 && yb == 0) p = 0;
            else if (xb == 1 && yb == 0) p = 3;
            else if (xb == 0 && yb == 1) p = 2;
            else p = 1;
            val += (long long)p * pw;
            pw *= 4;
            x >>= 1; y >>= 1;
        }
        cout << val << "\n";
    }
    return 0;
}
