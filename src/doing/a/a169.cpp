#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

// Doubled-coordinate trick: integer point x -> 2x, open gap (x,x+1) -> 2x+1.
// Range [0,65535] becomes [0,131070]. We maintain a segment tree over
// positions 0..MAXC-1 (MAXC=131071) tracking which positions are "in S".
// A position 2x represents integer point x; 2x+1 represents the open interval (x,x+1).
// Half-open segment [l,r) in doubled coords corresponds to all positions in [l,r-1].

const int MAXC = 131071; // 2*65535+1 = 131071, positions 0..131070
const int SIZE = 1 << 18; // 262144 > 2*131071, enough for segment tree

// Segment tree with lazy propagation supporting:
//   set to 0 (clear), set to 1 (fill), flip (XOR)
// Lazy tag: -1 = none, 0 = set to 0, 1 = set to 1, 2 = flip
struct SegTree {
    int cnt[SIZE];   // number of set positions in range
    int lazy[SIZE];  // -1 none, 0 set0, 1 set1, 2 flip

    void build(int node, int l, int r) {
        lazy[node] = -1;
        cnt[node] = 0;
        if (l == r) return;
        int m = (l + r) >> 1;
        build(node << 1, l, m);
        build(node << 1 | 1, m + 1, r);
    }

    void applySet(int node, int l, int r, int v) {
        lazy[node] = v;
        cnt[node] = v ? (r - l + 1) : 0;
    }

    void applyFlip(int node, int l, int r) {
        if (lazy[node] == 0) lazy[node] = 1;
        else if (lazy[node] == 1) lazy[node] = 0;
        else if (lazy[node] == 2) lazy[node] = -1;
        else lazy[node] = 2;
        cnt[node] = (r - l + 1) - cnt[node];
    }

    void push(int node, int l, int r) {
        if (lazy[node] == -1) return;
        int m = (l + r) >> 1;
        if (lazy[node] == 2) {
            applyFlip(node << 1, l, m);
            applyFlip(node << 1 | 1, m + 1, r);
        } else {
            applySet(node << 1, l, m, lazy[node]);
            applySet(node << 1 | 1, m + 1, r, lazy[node]);
        }
        lazy[node] = -1;
    }

    void pull(int node) {
        cnt[node] = cnt[node << 1] + cnt[node << 1 | 1];
    }

    // op: 0=set0, 1=set1, 2=flip, on range [L,R]
    void update(int node, int l, int r, int L, int R, int op) {
        if (R < l || r < L) return;
        if (L <= l && r <= R) {
            if (op == 2) applyFlip(node, l, r);
            else applySet(node, l, r, op);
            return;
        }
        push(node, l, r);
        int m = (l + r) >> 1;
        update(node << 1, l, m, L, R, op);
        update(node << 1 | 1, m + 1, r, L, R, op);
        pull(node);
    }

    // Collect set positions by DFS (only descending into non-empty ranges)
    // We instead do a direct traversal to gather maximal contiguous runs.
    void collect(int node, int l, int r, vector<pair<int,int>> &out, int &curStart, bool &inRun) {
        if (cnt[node] == 0) {
            if (inRun) { out.push_back({curStart, l - 1}); inRun = false; }
            return;
        }
        if (cnt[node] == (r - l + 1)) {
            if (!inRun) { curStart = l; inRun = true; }
            return;
        }
        push(node, l, r);
        int m = (l + r) >> 1;
        collect(node << 1, l, m, out, curStart, inRun);
        collect(node << 1 | 1, m + 1, r, out, curStart, inRun);
    }

    void gather(vector<pair<int,int>> &out) {
        bool inRun = false;
        int curStart = -1;
        collect(1, 0, MAXC - 1, out, curStart, inRun);
        if (inRun) out.push_back({curStart, MAXC - 1});
    }
};

SegTree st;

int main() {
    st.build(1, 0, MAXC - 1);

    char op;
    char lc, rc;
    int a, b;
    // Read commands until EOF. Each line: "X T" where T is like (a,b) [a,b) etc.
    while (scanf(" %c %c%d,%d%c", &op, &lc, &a, &b, &rc) == 5) {
        // convert to doubled coords
        // [a,b] -> [2a, 2b]
        // [a,b) -> [2a, 2b-1]
        // (a,b] -> [2a+1, 2b]
        // (a,b) -> [2a+1, 2b-1]
        int L, R;
        L = (lc == '[') ? 2 * a : 2 * a + 1;
        R = (rc == ']') ? 2 * b : 2 * b - 1;
        if (L > R) continue; // empty interval, no effect (e.g. (x,x))
        switch (op) {
            case 'U': // S = S ∪ T  : set [L,R] to 1
                st.update(1, 0, MAXC - 1, L, R, 1);
                break;
            case 'I': // S = S ∩ T  : set outside [L,R] to 0
                if (L > 0) st.update(1, 0, MAXC - 1, 0, L - 1, 0);
                if (R < MAXC - 1) st.update(1, 0, MAXC - 1, R + 1, MAXC - 1, 0);
                break;
            case 'D': // S = S - T  : set [L,R] to 0
                st.update(1, 0, MAXC - 1, L, R, 0);
                break;
            case 'C': // S = T - S  : flip [L,R], set outside [L,R] to 0
                if (L > 0) st.update(1, 0, MAXC - 1, 0, L - 1, 0);
                if (R < MAXC - 1) st.update(1, 0, MAXC - 1, R + 1, MAXC - 1, 0);
                st.update(1, 0, MAXC - 1, L, R, 2);
                break;
            case 'S': // S = S ⊕ T  : flip [L,R]
                st.update(1, 0, MAXC - 1, L, R, 2);
                break;
        }
    }

    vector<pair<int,int>> runs;
    st.gather(runs);

    if (runs.empty()) {
        printf("empty set\n");
    } else {
        bool first = true;
        for (auto &pr : runs) {
            int lo = pr.first, hi = pr.second;
            // decode doubled coords back to interval
            // even -> '[' or ']', odd -> '(' or ')'
            char lbr = (lo % 2 == 0) ? '[' : '(';
            char rbr = (hi % 2 == 0) ? ']' : ')';
            int la = lo / 2;
            int rb = (hi + 1) / 2; // for even hi=2b -> b; odd hi=2b-1 -> b
            // Verify: hi=2b (even) -> rb=(2b+1)/2=b. hi=2b-1 (odd) -> rb=2b/2=b. Good.
            if (!first) putchar(' ');
            first = false;
            printf("%c%d,%d%c", lbr, la, rb, rbr);
        }
        putchar('\n');
    }
    return 0;
}
