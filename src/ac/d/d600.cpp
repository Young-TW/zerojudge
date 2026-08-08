// d600 景觀餐廳 — 兩凸多邊形交集面積
// 演算法：Sutherland-Hodgman 凸多邊形裁剪 + shoelace 面積
// 自己手寫幾何模板。
//
// 輸入解析註記：本題提供的樣例 2.in 混入了一個殘缺行「14」
//（原題面 sample 本身的排版錯字），使方形土地被寫成 5 行才 4 個頂點。
// 因此改採「逐行解析、每個頂點需一行含兩個整數,否則略過該行」的方式，
// 這樣殘缺的單一整數行會被自然跳過；對正常測資（每行 x y）行為完全相同。
#include <bits/stdc++.h>
using namespace std;

struct P { double x, y; };

// (b-a) x (c-a)
static double cross3(const P& a, const P& b, const P& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 線段 p1p2 與直線 ab 的交點（呼叫時保證兩者跨越）
static P segLineIntersect(const P& p1, const P& p2, const P& a, const P& b) {
    double d1 = cross3(a, b, p1);
    double d2 = cross3(a, b, p2);
    double t = d1 / (d1 - d2);
    return { p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y) };
}

static double signedArea(const vector<P>& poly) {
    double s = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        const P& a = poly[i];
        const P& b = poly[(i + 1) % n];
        s += a.x * b.y - b.x * a.y;
    }
    return s / 2.0;
}

static void ensureCCW(vector<P>& poly) {
    if (signedArea(poly) < 0) reverse(poly.begin(), poly.end());
}

// 以 clip（凸、CCW）的每條邊裁剪 subject
static vector<P> clipPolygon(vector<P> subject, const vector<P>& clip) {
    const double EPS = 1e-9;
    int cn = clip.size();
    for (int e = 0; e < cn && !subject.empty(); ++e) {
        const P& A = clip[e];
        const P& B = clip[(e + 1) % cn];
        vector<P> out;
        int sn = subject.size();
        for (int i = 0; i < sn; ++i) {
            const P& cur = subject[i];
            const P& prev = subject[(i - 1 + sn) % sn];
            double dCur = cross3(A, B, cur);   // >=0 => 在邊內側(左側)
            double dPrev = cross3(A, B, prev);
            bool curIn = dCur >= -EPS;
            bool prevIn = dPrev >= -EPS;
            if (curIn) {
                if (!prevIn) out.push_back(segLineIntersect(prev, cur, A, B));
                out.push_back(cur);
            } else if (prevIn) {
                out.push_back(segLineIntersect(prev, cur, A, B));
            }
        }
        subject.swap(out);
    }
    return subject;
}

// 逐行讀取：跳過不含兩個整數的行，取得 n 個頂點
static vector<P> readPoly(int n) {
    vector<P> r;
    string line;
    while ((int)r.size() < n && getline(cin, line)) {
        istringstream ss(line);
        double x, y;
        if (ss >> x >> y) r.push_back({ x, y });
    }
    return r;
}

// 讀取一個計數（跳到第一個能解析出整數的行）
static int readCount() {
    string line;
    while (getline(cin, line)) {
        istringstream ss(line);
        long v;
        if (ss >> v) return (int)v;
    }
    return -1;
}

int main() {
    int M = readCount();
    vector<P> land = readPoly(M);
    int N = readCount();
    vector<P> fac = readPoly(N);

    ensureCCW(land);
    ensureCCW(fac);

    vector<P> inter = clipPolygon(fac, land);

    double area = fabs(signedArea(inter));
    if (area < 5e-9) area = 0.0;

    printf("%.2f\n", area);
    return 0;
}
