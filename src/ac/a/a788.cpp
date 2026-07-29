// a788. uPhone Two-Point Zoom
// 自寫解答 (self-written; no external source copied)
//
// 每行 8 個整數 = 4 個點:
//   f1 起點(x1,y1) f1 終點(x2,y2) f2 起點(x3,y3) f2 終點(x4,y4)
// 讀到 8 個零結束。
//
// 起始兩點 = f1 起點與 f2 起點;結束兩點 = f1 終點與 f2 終點。
//   相對移動 = 結束兩點中心 - 起始兩點中心 (無條件捨去到整數位 = 向零截斷/truncate)
//   放大率   = 結束兩點距離 / 起始兩點距離 (四捨五入到小數第三位)
//   旋轉角度 = atan((m2-m1)/(1+m1*m2)) 弧度 (四捨五入到小數第三位)
//     m1 = 起始兩點連線斜率, m2 = 結束兩點連線斜率 (題目保證無垂直線)
#include <bits/stdc++.h>
using namespace std;
int main(){
    long long x1,y1,x2,y2,x3,y3,x4,y4;
    while(cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4){
        if(x1==0&&y1==0&&x2==0&&y2==0&&x3==0&&y3==0&&x4==0&&y4==0) break;
        // 中心座標 * 2 (以整數運算避免半整數的浮點誤差)
        long long dx2=(x2+x4)-(x1+x3); // 2*(x 方向移動)
        long long dy2=(y2+y4)-(y1+y3); // 2*(y 方向移動)
        long long moveX=dx2/2, moveY=dy2/2; // 整數除法向零截斷 = 無條件捨去
        // 兩點距離
        double sd=hypot((double)(x3-x1),(double)(y3-y1)); // 起始兩點距離
        double ed=hypot((double)(x4-x2),(double)(y4-y2)); // 結束兩點距離
        double mag=ed/sd;
        // 兩連線斜率
        double m1=(double)(y3-y1)/(double)(x3-x1);
        double m2=(double)(y4-y2)/(double)(x4-x2);
        double ang=atan((m2-m1)/(1.0+m1*m2));
        // 四捨五入 (round-half-away-from-zero) 到小數第三位
        double magR=round(mag*1000.0)/1000.0;
        double angR=round(ang*1000.0)/1000.0;
        if(magR==0.0) magR=0.0;
        if(angR==0.0) angR=0.0;      // 消除 -0.000
        printf("%lld %lld %.3f %.3f\n", moveX, moveY, magR+0.0, angR+0.0);
    }
    return 0;
}
