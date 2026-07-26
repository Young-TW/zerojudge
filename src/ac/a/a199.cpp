#include <bits/stdc++.h>
using namespace std;

struct LiChao {
    struct Line {
        long double m, b;                 // y = m * x + b
        Line(long double _m = 0, long double _b = -1e300) : m(_m), b(_b) {}
        inline long double get(long double x) const { return m * x + b; }
    };
    struct Node {
        Line line;
        Node *l, *r;
        Node(const Line& ln) : line(ln), l(nullptr), r(nullptr) {}
    };
    long double X_L, X_R;
    Node* root;
    LiChao(long double l, long double r) : X_L(l), X_R(r), root(nullptr) {}

    void insert_line(const Line& nw) { insert(root, X_L, X_R, nw); }

    void insert(Node* &node, long double l, long double r, Line nw) {
        if (!node) { node = new Node(nw); return; }
        long double mid = (l + r) * 0.5L;
        bool left = nw.get(l) > node->line.get(l);
        bool middle = nw.get(mid) > node->line.get(mid);
        if (middle) swap(node->line, nw);
        if (r - l < 1e-12L) return;
        if (left != middle) insert(node->l, l, mid, nw);
        else                insert(node->r, mid, r, nw);
    }

    long double query(long double x) const {
        return query(root, X_L, X_R, x);
    }

    long double query(Node* node, long double l, long double r, long double x) const {
        if (!node) return -1e300L;
        long double cur = node->line.get(x);
        if (r - l < 1e-12L) return cur;
        long double mid = (l + r) * 0.5L;
        if (x < mid) return max(cur, query(node->l, l, mid, x));
        else        return max(cur, query(node->r, mid, r, x));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    double S_input;
    while (cin >> N >> S_input) {
        vector<long double> A(N), B(N), R(N), X(N);
        long double xmin = 1e300L, xmax = -1e300L;
        for (int i = 0; i < N; ++i) {
            double a,b,r;
            cin >> a >> b >> r;
            A[i] = a; B[i] = b; R[i] = r;
            X[i] = A[i] / B[i];
            xmin = min(xmin, X[i]);
            xmax = max(xmax, X[i]);
        }
        if (xmax - xmin < 1e-12L) {          // all equal, give a tiny interval
            xmax = xmin + 1.0L;
        }
        LiChao lichao(xmin, xmax);
        long double best = S_input;          // current maximal cash
        for (int i = 0; i < N; ++i) {
            if (lichao.root) {
                long double y = lichao.query(X[i]);          // max_i (Pi * x + Qi)
                long double cand = y * B[i];
                if (cand > best) best = cand;
            }
            // create line for this day
            long double den = R[i] * A[i] + B[i];
            long double P = best * R[i] / den;
            long double Q = best / den;
            lichao.insert_line({P, Q});
        }
        cout.setf(ios::fixed); cout << setprecision(3) << (double)best << '\n';
    }
    return 0;
}
