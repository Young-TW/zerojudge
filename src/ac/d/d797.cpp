#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;
typedef unsigned long long U;

struct N {
    int k;
    U v;
    vector<N> ch;
};

N num(U v) { return {0, v, {}}; }
N mkPow(U b, N e) {
    if (e.k == 0) {
        if (e.v == 0) return num(1);
        if (e.v == 1) return num(b);
    }
    return {1, b, {e}};
}
N mkTerm(U c, N p) {
    if (c == 1) return p;
    if (p.k == 0 && p.v == 1) return num(c);
    return {2, c, {p}};
}

struct L {
    vector<string> g;
    int w, h;
};

L CL(const N& n) {
    if (n.k == 0) {
        L r;
        r.g = {to_string(n.v)};
        r.w = r.g[0].size();
        r.h = 1;
        return r;
    }
    if (n.k == 1) {
        L e = CL(n.ch[0]);
        string bs = to_string(n.v);
        int bw = bs.size();
        int ew = e.w;
        int eh = e.h;
        int H = eh + 1;
        int W = bw + ew;
        L r;
        r.g.assign(H, string(W, ' '));
        r.w = W;
        r.h = H;
        int br = H - 1;
        for (int i = 0; i < bw; i++) r.g[br][i] = bs[i];
        int et = H - 2 - (eh - 1);
        for (int rr = 0; rr < eh; rr++)
            for (int c = 0; c < ew; c++)
                r.g[et + rr][bw + c] = e.g[rr][c];
        return r;
    }
    if (n.k == 2) {
        L p = CL(n.ch[0]);
        string cs = to_string(n.v);
        int cw = cs.size();
        int W = cw + 1 + p.w;
        int H = p.h;
        L r;
        r.g.assign(H, string(W, ' '));
        r.w = W;
        r.h = H;
        int br = H - 1;
        for (int i = 0; i < cw; i++) r.g[br][i] = cs[i];
        r.g[br][cw] = '*';
        for (int rr = 0; rr < p.h; rr++)
            for (int c = 0; c < p.w; c++)
                r.g[rr][cw + 1 + c] = p.g[rr][c];
        return r;
    }
    vector<L> tl;
    for (auto& t : n.ch) tl.push_back(CL(t));
    int H = 0, W = 0;
    for (auto& l : tl) H = max(H, l.h);
    for (size_t i = 0; i < tl.size(); i++) {
        if (i) W++;
        W += tl[i].w;
    }
    L r;
    r.g.assign(H, string(W, ' '));
    r.w = W;
    r.h = H;
    int br = H - 1;
    int col = 0;
    for (size_t i = 0; i < tl.size(); i++) {
        if (i) {
            r.g[br][col] = '+';
            col++;
        }
        L& l = tl[i];
        int off = br - (l.h - 1);
        for (int rr = 0; rr < l.h; rr++)
            for (int c = 0; c < l.w; c++)
                r.g[off + rr][col + c] = l.g[rr][c];
        col += l.w;
    }
    return r;
}

N build(U n, U b) {
    if (n < b) return num(n);
    U p = 1;
    int k = 0;
    while (p <= n / b) {
        p *= b;
        k++;
    }
    vector<N> ts;
    U rem = n;
    while (rem > 0) {
        if (p <= rem) {
            U c = rem / p;
            rem %= p;
            N pw;
            if (k == 0) pw = num(1);
            else if (k == 1) pw = num(b);
            else pw = mkPow(b, build((U)k, b));
            ts.push_back(mkTerm(c, pw));
        }
        p /= b;
        k--;
    }
    if (ts.size() == 1) return ts[0];
    return {3, 0, ts};
}

L bpl(const N& part, const string& pre, int H, bool first) {
    L pl = CL(part);
    int P = pre.size();
    int lead = first ? 0 : 1;   // continuation parts start with a '+' connector
    int W = P + lead + pl.w;
    L r;
    r.g.assign(H, string(W, ' '));
    r.w = W;
    r.h = H;
    int br = H - 1;
    if (first)
        for (int i = 0; i < P; i++) r.g[br][i] = pre[i];
    else
        r.g[br][P] = '+';
    int off = br - (pl.h - 1);
    for (int rr = 0; rr < pl.h; rr++)
        for (int c = 0; c < pl.w; c++)
            r.g[off + rr][P + lead + c] = pl.g[rr][c];
    return r;
}

string tr(const string& s) {
    size_t e = s.find_last_not_of(' ');
    if (e == string::npos) return "";
    return s.substr(0, e + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    U n, b;
    bool first_case = true;
    while (cin >> n >> b) {
        if (n == 0 && b == 0) break;
        if (!first_case) cout << string(80, '-') << "\n";
        first_case = false;
        N expr = build(n, b);
        int H = CL(expr).h;
        string pre = to_string(n) + " = ";
        int P = pre.size();
        int msw = 80 - P;
        if (msw < 0) msw = 0;
        
        vector<N> parts;
        if (expr.k == 3) {
            vector<N> cg;
            int cw = 0;
            bool contGroup = false;   // groups after the first begin with a '+'
            for (auto& t : expr.ch) {
                int tw = CL(t).w;
                if (cg.empty()) {
                    cg.push_back(t);
                    // continuation groups reserve one column for the leading '+'
                    cw = tw + (contGroup ? 1 : 0);
                } else {
                    int nw = cw + 1 + tw;
                    if (nw <= msw) {
                        cg.push_back(t);
                        cw = nw;
                    } else {
                        parts.push_back(cg.size() == 1 ? cg[0] : N{3, 0, cg});
                        cg.clear();
                        contGroup = true;
                        cg.push_back(t);
                        cw = tw + 1;   // reserve column for leading '+'
                    }
                }
            }
            if (!cg.empty())
                parts.push_back(cg.size() == 1 ? cg[0] : N{3, 0, cg});
        } else {
            parts.push_back(expr);
        }
        
        cout << n << " in complete base " << b << ":\n";
        for (size_t i = 0; i < parts.size(); i++) {
            cout << "\n";
            L pl = bpl(parts[i], pre, H, i == 0);
            for (int rr = 0; rr < pl.h; rr++)
                cout << tr(pl.g[rr]) << "\n";
        }
    }
    return 0;
}
