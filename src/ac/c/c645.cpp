// c645 魔術箱 — 自寫解答
//
// 六個盒子 B1..B6 各起始 1 枚。操作：
//   type1 j (1<=j<=5): Bj-1, B(j+1)+2
//   type2 k (1<=k<=4): Bk-1, 交換 B(k+1),B(k+2)
// 目標：B1..B5=0 且 B6=n。輸出任一組合法操作序列(special judge)。
//
// 作法(自創)：
//  1. 把左側 B1..B5 的硬幣全部匯進 B4，同時把累加器(B5,B6)清成 0，
//     形成乾淨狀態 (0,0,0,P,0,0)。用 op1 逐級右推 + 用 B5 當暫存做
//     recycle(op1 B4 倍增 + op2 B3 換回) 把 B4 疊到夠大。
//  2. 在 B5=B6=0 時，op2 B4 交換兩個 0 是「無副作用」的，可任意「燒掉」多餘
//     的控制幣，把 B4 精準降到 X = C + seedCost。
//  3. seed：由空累加器用 op1 B4 (推偶數到 B5) + op2 B4 (換到 B6) 造出偶數 seed。
//  4. Phase B：把 n 反向化簡到 seed(除以2 或 減3)，再正向重建：
//       DOUBLE f->2f  : op2 B4 ; op1 B5 x f
//       ADD3   f->f+3 : op2 B4 ; op1 B5 ; op2 B4 ; op1 B5 x2
//     這些 op2 B4 恰好用掉 C 個控制幣，結束時 B4=0。
//  總操作數 約等於 n(理論下限為 n-6),不會 OLE。
#include <cstdio>
#include <cstdlib>

static int b[8]; // b[1..6]

// ---- 快速輸出 ----
static char *obuf;
static size_t opos = 0, ocap;
static inline void flushOut() { fwrite(obuf, 1, opos, stdout); opos = 0; }
static inline void put4(int op, int box) {
    if (opos + 8 > ocap) flushOut();
    obuf[opos++] = char('0' + op);
    obuf[opos++] = ' ';
    obuf[opos++] = char('0' + box);
    obuf[opos++] = '\n';
}

// ---- 帶模擬的發射 ----
static inline void emit(int op, int box) {
    if (op == 1) { b[box] -= 1; b[box + 1] += 2; }
    else { b[box] -= 1; int t = b[box + 1]; b[box + 1] = b[box + 2]; b[box + 2] = t; }
    put4(op, box);
}
static inline void op1(int box, long long t) { while (t-- > 0) emit(1, box); }
static inline void op2(int box, long long t) { while (t-- > 0) emit(2, box); }

// 化簡 n 到偶數 seed，回傳 seed；正向步驟存於 fwd('D'/'A')，控制數 C
static char fwd[256];
static int fwdlen;
static int reduceEven(int n, int *pC) {
    static char back[256];
    int bl = 0, t = n;
    while (t > 4) {
        if (t % 2 == 0) { back[bl++] = 'D'; t /= 2; }
        else { back[bl++] = 'A'; t -= 3; }
    }
    int seed;
    if (t == 2 || t == 4) seed = t;
    else if (t == 1) { bl--; seed = 2; }   // 去掉最後的 D(2->1)
    else /* t==3 */   { bl--; seed = 6; }   // 去掉最後的 D(6->3)
    fwdlen = 0;
    int C = 0;
    for (int i = bl - 1; i >= 0; --i) {
        fwd[fwdlen++] = back[i];
        C += (back[i] == 'D') ? 1 : 2;
    }
    *pC = C;
    return seed;
}

static int buildCleanPile0(int Pmin) {
    op1(1, 1);        // B2=3
    op1(2, 3);        // B3=7
    op1(5, 1);        // B6=3
    op2(4, 1);        // B5=3,B6=0
    op2(3, 1);        // B4=3,B5=0,B3=6
    while (b[4] < Pmin && b[3] >= 1) {
        int v = b[4];
        op1(4, v);    // B4->B5 = 2v
        op2(3, 1);    // 換回: B4=2v
    }
    if (b[3] > 0) op1(3, b[3]); // 把 B3 剩餘全倒入 B4
    return b[4];
}

static void seedEmpty(int v) {
    op1(4, v / 2);    // B5=v
    op2(4, 1);        // B6=v, B5=0
}

static void phaseB() {
    for (int i = 0; i < fwdlen; ++i) {
        int f = b[6];   // 目前 B6(累加器值)
        if (fwd[i] == 'D') {
            op2(4, 1);
            op1(5, f);          // B6=2f
        } else {
            op2(4, 1);
            op1(5, 1);
            op2(4, 1);
            op1(5, 2);          // B6=f+3
        }
    }
}

// 小 n 固定序列(由自寫 BFS 求得)
static void small(int n) {
    switch (n) {
        case 0: { int s[][2]={{2,4},{2,3},{2,1},{2,4},{2,3},{2,4}}; for(auto&p:s)emit(p[0],p[1]); break; }
        case 1: { int s[][2]={{2,1},{2,4},{2,3},{2,2},{2,3}}; for(auto&p:s)emit(p[0],p[1]); break; }
        case 2: { int s[][2]={{1,4},{2,3},{2,1},{2,4},{2,3},{2,4}}; for(auto&p:s)emit(p[0],p[1]); break; }
        case 3: { int s[][2]={{1,5},{2,1},{2,4},{2,2},{2,4}}; for(auto&p:s)emit(p[0],p[1]); break; }
        case 4: { int s[][2]={{1,3},{2,1},{2,4},{2,3},{2,4},{1,5}}; for(auto&p:s)emit(p[0],p[1]); break; }
        case 5: { int s[][2]={{1,3},{2,1},{2,3},{2,4},{1,5}}; for(auto&p:s)emit(p[0],p[1]); break; }
        case 6: { int s[][2]={{1,1},{1,2},{1,2},{2,2},{2,4},{2,3},{2,4},{1,5}}; for(auto&p:s)emit(p[0],p[1]); break; }
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    ocap = 1 << 20;
    obuf = (char *)malloc(ocap);

    for (int i = 1; i <= 6; ++i) b[i] = 1;

    if (n <= 6) {
        small(n);
    } else {
        int C;
        int seed = reduceEven(n, &C);
        int seedcost = seed / 2 + 1;
        int X = C + seedcost;
        int P = buildCleanPile0(X);
        op2(4, P - X);       // 無副作用地燒掉多餘控制幣 (B5=B6=0)
        seedEmpty(seed);     // 造 seed，B4 剩 C
        phaseB();            // 用掉 C 個控制幣，B6=n，B4=0
    }

    flushOut();
    free(obuf);
    return 0;
}
