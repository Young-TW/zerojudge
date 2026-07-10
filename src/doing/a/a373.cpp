#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;

static char ibuf[1 << 20];
static int ipos = 0, ilen = 0;
inline int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}
inline long long readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    bool neg = false;
    if (c == '-') { neg = true; c = gc(); }
    long long x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

const int MAXN = 250005;
int X[MAXN], V[MAXN];
int prv[MAXN], nxt[MAXN];
int N;

struct Event {
    int i, j; // i behind j (smaller index), V[i] > V[j]
};

struct Cmp {
    bool operator()(const Event &a, const Event &b) const {
        // min-heap by (time, position); priority_queue is max-heap so return true if a > b
        long long na = X[a.j] - X[a.i], da = V[a.i] - V[a.j]; // time_a = na/da
        long long nb = X[b.j] - X[b.i], db = V[b.i] - V[b.j]; // time_b = nb/db
        long long ta = na * db, tb = nb * da;
        if (ta != tb) return ta > tb;
        long long pa = (long long)V[a.i] * X[a.j] - (long long)X[a.i] * V[a.j]; // pos_a = pa/da
        long long pb = (long long)V[b.i] * X[b.j] - (long long)X[b.i] * V[b.j]; // pos_b = pb/db
        long long qa = pa * db, qb = pb * da;
        if (qa != qb) return qa > qb;
        if (a.i != b.i) return a.i > b.i;
        return a.j > b.j;
    }
};

int main() {
    N = (int)readInt();
    for (int i = 1; i <= N; i++) {
        X[i] = (int)readInt();
        V[i] = (int)readInt();
    }

    // inversion count mod 1e6 via BIT over speeds 1..100
    int bit[102];
    memset(bit, 0, sizeof(bit));
    long long total = 0;
    const long long MOD = 1000000;
    for (int j = 1; j <= N; j++) {
        long long le = 0;
        for (int v = V[j]; v > 0; v -= v & (-v)) le += bit[v];
        long long inv = (j - 1) - le;
        total = (total + inv) % MOD;
        for (int v = V[j]; v <= 100; v += v & (-v)) bit[v]++;
    }

    // linked list by current position order
    for (int i = 1; i <= N; i++) { prv[i] = i - 1; nxt[i] = i + 1; }
    nxt[N] = 0;
    prv[1] = 0;

    priority_queue<Event, vector<Event>, Cmp> pq;
    auto pushPair = [&](int a, int b) {
        if (a == 0 || b == 0) return;
        if (V[a] > V[b]) pq.push({a, b});
    };
    for (int i = 1; i + 1 <= N; i++) pushPair(i, i + 1);

    string out;
    out.reserve(1 << 20);
    char tmp[64];
    int len = sprintf(tmp, "%lld\n", total);
    out.append(tmp, len);

    int emitted = 0;
    const int LIMIT = 10000;
    while (emitted < LIMIT && !pq.empty()) {
        Event e = pq.top(); pq.pop();
        int a = e.i, b = e.j;
        if (nxt[a] != b || prv[b] != a) continue; // stale
        len = sprintf(tmp, "%d %d\n", a, b);
        out.append(tmp, len);
        emitted++;
        // swap a,b -> new order: p, b, a, q
        int p = prv[a], q = nxt[b];
        if (p != 0) nxt[p] = b;
        prv[b] = p;
        nxt[b] = a;
        prv[a] = b;
        nxt[a] = q;
        if (q != 0) prv[q] = a;
        pushPair(p, b);
        pushPair(a, q);
    }

    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
