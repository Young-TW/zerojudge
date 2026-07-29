// ZeroJudge e033 - 摩天大樓
// n<=25 層, k<=4 個公共設施, n-k 戶住戶。
// 住戶滿意度 = min_i |f_i - L| * a_i  (f_i 為第 i 個設施樓層, L 為住戶樓層)
// 目標: 最大化「最低住戶滿意度」。
//
// 作法: 列舉 k 個(可區分)設施的有序樓層排列 P(n,k)。固定設施位置後, 其餘 m=n-k
// 個樓層與 m 戶住戶構成二分圖, S[floor][house] 為滿意度; 求「最大化最小邊」的完美
// 匹配(瓶頸匹配)。答案取所有設施排列中的最大值。
//
// 加速:
//   1. 上下反轉對稱 (floor -> n+1-floor) 解相同, 僅處理字典序較小(或相等)者。
//   2. 上界剪枝: 瓶頸值 <= min(每列最大值) 且 <= min(每行最大值); 上界 <= 目前最佳則跳過。
//   3. 只在「能突破目前最佳」(edges>best 存在完美匹配) 時才二分求確切瓶頸值。
// 匹配以位元遮罩 Kuhn 實作。最壞 n=25,k=4 實測 ~0.2s。
#include <bits/stdc++.h>
using namespace std;

int n, k, m;              // m = n-k
int S[25][25];            // S[free-floor row][household col]
int adj[25];              // 目前門檻下的鄰接位元遮罩
int matchCol[25];

static inline bool tryK(int r, unsigned &vis) {
    unsigned a = (unsigned)adj[r] & ~vis;
    while (a) {
        int c = __builtin_ctz(a);
        a &= a - 1;
        vis |= (1u << c);
        if (matchCol[c] == -1 || tryK(matchCol[c], vis)) {
            matchCol[c] = r;
            return true;
        }
    }
    return false;
}

// 只用 S >= t 的邊時是否存在完美匹配
bool canMatch(int t) {
    for (int r = 0; r < m; r++) {
        int mask = 0;
        for (int c = 0; c < m; c++)
            if (S[r][c] >= t) mask |= (1 << c);
        adj[r] = mask;
    }
    for (int c = 0; c < m; c++) matchCol[c] = -1;
    for (int r = 0; r < m; r++) {
        unsigned vis = 0;
        if (!tryK(r, vis)) return false; // 某列無法匹配 => 最大匹配 < m
    }
    return true;
}

int a[25][4];             // 住戶對各設施的厭惡度
int f[4];                 // 設施樓層 (1-indexed)
int freeFloor[25];
bool usedFloor[26];
int best;

void evaluate() {
    // 反轉對稱: 若 reflect(f) 字典序較小則跳過
    for (int i = 0; i < k; i++) {
        int rv = n + 1 - f[i];
        if (rv < f[i]) return;
        if (rv > f[i]) break;
    }
    // 其餘樓層
    m = n - k;
    int mm = 0;
    for (int i = 1; i <= n; i++) usedFloor[i] = false;
    for (int i = 0; i < k; i++) usedFloor[f[i]] = true;
    for (int i = 1; i <= n; i++) if (!usedFloor[i]) freeFloor[mm++] = i;

    // 建 S 並算列/行最大值
    int minRowMax = INT_MAX;
    int colMax[25];
    for (int c = 0; c < m; c++) colMax[c] = 0;
    for (int r = 0; r < m; r++) {
        int L = freeFloor[r];
        int d[4];
        for (int i = 0; i < k; i++) d[i] = abs(f[i] - L);
        int rowMax = 0;
        for (int c = 0; c < m; c++) {
            int v = INT_MAX;
            for (int i = 0; i < k; i++) {
                int t = d[i] * a[c][i];
                if (t < v) v = t;
            }
            S[r][c] = v;
            if (v > rowMax) rowMax = v;
            if (v > colMax[c]) colMax[c] = v;
        }
        if (rowMax < minRowMax) minRowMax = rowMax;
    }
    int cand = minRowMax;
    for (int c = 0; c < m; c++) if (colMax[c] < cand) cand = colMax[c];
    if (cand <= best) return;

    if (!canMatch(best + 1)) return;         // 無法突破目前最佳
    int lo = best + 1, hi = cand;            // 二分求確切瓶頸值
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        if (canMatch(mid)) lo = mid; else hi = mid - 1;
    }
    best = lo;
}

void genOrdered(int idx) {
    if (idx == k) { evaluate(); return; }
    for (int fl = 1; fl <= n; fl++) {
        if (usedFloor[fl]) continue;
        usedFloor[fl] = true;
        f[idx] = fl;
        genOrdered(idx + 1);
        usedFloor[fl] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> k) {
        m = n - k;
        for (int j = 0; j < m; j++)
            for (int i = 0; i < k; i++)
                cin >> a[j][i];
        best = 0;
        for (int i = 1; i <= n; i++) usedFloor[i] = false;
        genOrdered(0);
        cout << best << "\n";
    }
    return 0;
}
