// k187. pD. 分子環 (molecule)
// 自寫解答 (100% self-written, no external code copied).
//
// 模型推導:
//  分子環 = X 段與 Y 段交替出現的環 (各 R 段, R>=1), 或整環同一分子。
//  某位置的分類取決於「兩個鄰居」的分子:
//    - X 段內部位置(兩鄰皆 X) 計入 a; 長度 1 的 Y 段(兩鄰皆 X) 也計入 a。
//    - Y 段內部位置 與 長度 1 的 X 段 計入 b。
//    - 長度>=2 的段, 其頭尾兩位置各有一個異種鄰居 → 每個長段貢獻 2 到 c。
//  由此:
//    c 必為偶數;  nx = a + c/2 個 X ; ny = b + c/2 個 Y ; n = a+b+c。
//    令 m = c/2 = 「長度>=2 的段」總數。 設 LX 個長 X 段, LY = m-LX 個長 Y 段。
//    設 R = X 段數 = Y 段數。 則 X 段中 (R-LX) 個為單點, Y 段中 (R-LY) 個為單點。
//    長 X 段共放 nx-R+LX 個 X (需 >= 2*LX → R <= nx-LX);  長 Y 段同理 R <= ny-LY。
//    可行需 R >= max(1,LX,LY)。
//  不穩定度 K = 最長段長度。 對固定 LX, K 對 R 單調不增 → 取 R = min(nx-LX, ny-LY) 最佳。
//  枚舉 LX = 0..m 取最小 K (sum m <= 1e5, 高效)。 無可行 LX → 輸出 -1。
//  c 為奇數 → 無解 -1。 整環同種 (nx==0 或 ny==0) → K = n。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    if (!(cin >> T)) return 0;
    string out;
    out.reserve(1 << 20);

    while (T--) {
        long long a, b, c;
        cin >> a >> b >> c;

        if (c % 2 != 0) { out += "-1\n"; continue; }
        long long half = c / 2;
        long long nx = a + half, ny = b + half;
        long long n = a + b + c;

        // 整環同一分子
        if (nx == 0) { out += to_string(n) + "\n" + string((size_t)n, 'Y') + "\n"; continue; }
        if (ny == 0) { out += to_string(n) + "\n" + string((size_t)n, 'X') + "\n"; continue; }

        long long m = half;
        long long bestK = LLONG_MAX, bR = -1, bLX = -1;

        for (long long LX = 0; LX <= m; ++LX) {
            long long LY = m - LX;
            long long R = -1, maxX = 0, maxY = 0;
            bool ok = false;

            if (LX == 0 && LY == 0) {
                // c == 0 : 兩側皆單點, 需 nx == ny
                if (nx == ny) { R = nx; if (R >= 1) { ok = true; maxX = 1; maxY = 1; } }
            } else if (LX == 0) {
                // X 全單點 → R = nx
                R = nx;
                if (R >= max(1LL, LY) && R <= ny - LY) {
                    ok = true; maxX = 1;
                    long long dY = ny - R;
                    maxY = 1 + (LY > 0 ? (dY + LY - 1) / LY : 0);
                }
            } else if (LY == 0) {
                R = ny;
                if (R >= max(1LL, LX) && R <= nx - LX) {
                    ok = true; maxY = 1;
                    long long dX = nx - R;
                    maxX = 1 + (dX + LX - 1) / LX;
                }
            } else {
                long long Rhi = min(nx - LX, ny - LY);
                long long Rlo = max(1LL, max(LX, LY));
                if (Rhi >= Rlo) {
                    R = Rhi; ok = true;
                    long long dX = nx - R, dY = ny - R;
                    maxX = 1 + (dX + LX - 1) / LX;
                    maxY = 1 + (dY + LY - 1) / LY;
                }
            }

            if (ok) {
                long long K = max(maxX, maxY);
                if (K < bestK) { bestK = K; bR = R; bLX = LX; }
            }
        }

        if (bestK == LLONG_MAX) { out += "-1\n"; continue; }

        // 建構字串
        long long R = bR, LX = bLX, LY = m - LX;
        vector<long long> xb, yb;
        xb.reserve((size_t)R); yb.reserve((size_t)R);

        if (LX > 0) {
            long long tot = nx - R + LX, base = tot / LX, rem = tot % LX;
            for (long long i = 0; i < LX; ++i) xb.push_back(base + (i < rem ? 1 : 0));
        }
        for (long long i = 0, pX = R - LX; i < pX; ++i) xb.push_back(1);

        if (LY > 0) {
            long long tot = ny - R + LY, base = tot / LY, rem = tot % LY;
            for (long long i = 0; i < LY; ++i) yb.push_back(base + (i < rem ? 1 : 0));
        }
        for (long long i = 0, qY = R - LY; i < qY; ++i) yb.push_back(1);

        string M;
        M.reserve((size_t)n);
        for (long long i = 0; i < R; ++i) {
            M.append((size_t)xb[i], 'X');
            M.append((size_t)yb[i], 'Y');
        }
        out += to_string(bestK) + "\n" + M + "\n";
    }

    cout << out;
    return 0;
}
