#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
using i128 = __int128_t;

//------------------------------------------------------------
//  F(U,V) = sum_{0<=u<=U} sum_{0<=v<=V} max(u,v)
static i128 sumMax0toUV(int64 U, int64 V) {
    if (U < 0 || V < 0) return 0;
    if (U > V) swap(U, V);                 // now U <= V
    i128 u = U, v = V;
    // term1 = U*(U+1)*(4U+5)/6
    i128 term1 = u * (u + 1) * (4 * u + 5) / 6;
    // term2 = (U+1)*( V*(V+1) - U*(U+1) )/2
    i128 term2 = (u + 1) * (v * (v + 1) - u * (u + 1)) / 2;
    return term1 + term2;
}

//------------------------------------------------------------
//  sum of max(u,v) on rectangle [a..b] x [c..d] (a,b,c,d >= 0)
static i128 maxSumRange(int64 a, int64 b, int64 c, int64 d) {
    if (a > b || c > d) return 0;
    i128 res = 0;
    res += sumMax0toUV(b, d);
    res -= sumMax0toUV(a - 1, d);
    res -= sumMax0toUV(b, c - 1);
    res += sumMax0toUV(a - 1, c - 1);
    return res;
}

//------------------------------------------------------------
//  prefix sum P(x,y)  (x,y >= 1)
static i128 prefixSum(int64 N, int64 x, int64 y) {
    if (x <= 0 || y <= 0) return 0;

    int64 xl = min<int64>(x, N);          // columns on the left side (including centre)
    int64 xr = max<int64>(0, x - N);      // columns on the right side
    int64 yl = min<int64>(y, N);          // rows at the bottom side (including centre)
    int64 yr = max<int64>(0, y - N);      // rows at the top side

    i128 total = 0;

    // bottom‑left quadrant
    if (xl > 0 && yl > 0) {
        int64 a = N - xl;          // u low
        int64 b = N - 1;           // u high
        int64 c = N - yl;          // v low
        int64 d = N - 1;           // v high
        i128 cnt = (i128)xl * (i128)yl;
        total += cnt;                              // the "+1" of each cell
        total += maxSumRange(a, b, c, d);
    }

    // bottom‑right quadrant
    if (xr > 0 && yl > 0) {
        int64 a = 1;
        int64 b = xr;
        int64 c = N - yl;
        int64 d = N - 1;
        i128 cnt = (i128)xr * (i128)yl;
        total += cnt;
        total += maxSumRange(a, b, c, d);
    }

    // top‑left quadrant
    if (xl > 0 && yr > 0) {
        int64 a = N - xl;
        int64 b = N - 1;
        int64 c = 1;
        int64 d = yr;
        i128 cnt = (i128)xl * (i128)yr;
        total += cnt;
        total += maxSumRange(a, b, c, d);
    }

    // top‑right quadrant
    if (xr > 0 && yr > 0) {
        int64 a = 1;
        int64 b = xr;
        int64 c = 1;
        int64 d = yr;
        i128 cnt = (i128)xr * (i128)yr;
        total += cnt;
        total += maxSumRange(a, b, c, d);
    }

    return total;
}

//------------------------------------------------------------
static string i128ToString(i128 x) {
    if (x == 0) return "0";
    bool neg = false;
    if (x < 0) { neg = true; x = -x; }
    string s;
    while (x > 0) {
        int digit = int(x % 10);
        s.push_back('0' + digit);
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

//------------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 N;
    while ( (cin >> N) ) {
        int64 x1, y1, x2, y2;
        if (!(cin >> x1 >> y1 >> x2 >> y2)) break;
        int64 xmin = min(x1, x2), xmax = max(x1, x2);
        int64 ymin = min(y1, y2), ymax = max(y1, y2);

        i128 ans = 0;
        ans += prefixSum(N, xmax, ymax);
        ans -= prefixSum(N, xmin - 1, ymax);
        ans -= prefixSum(N, xmax, ymin - 1);
        ans += prefixSum(N, xmin - 1, ymin - 1);

        cout << i128ToString(ans) << '\n';
    }
    return 0;
}
