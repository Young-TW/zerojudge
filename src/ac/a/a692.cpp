#include <cstdio>
#include <vector>
using namespace std;

static inline int gc() {
    static char buf[1 << 16];
    static int len = 0, pos = 0;
    if (pos == len) {
        len = (int)fread(buf, 1, sizeof(buf), stdin);
        pos = 0;
        if (len == 0) return -1;
    }
    return buf[pos++];
}

static inline long long readLL() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    if (c == -1) return -1;
    long long x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return x;
}

int main() {
    while (true) {
        long long nn = readLL();
        if (nn < 0) break;
        long long kk = readLL();
        int n = (int)nn, k = (int)kk;

        vector<long long> l(n);
        long long total = 0;
        for (int i = 0; i < n; i++) {
            l[i] = readLL();
            total += l[i];
        }

        if (n == 1) {
            printf("%lld\n", l[0]);
            continue;
        }

        int m = 2 * (n - 1);
        vector<int> to(m), nxt(m);
        vector<int> head(n, -1);
        for (int i = 0; i < n - 1; i++) {
            int u = (int)readLL() - 1;
            int v = (int)readLL() - 1;
            to[2*i] = v;     nxt[2*i] = head[u]; head[u] = 2*i;
            to[2*i+1] = u;   nxt[2*i+1] = head[v]; head[v] = 2*i+1;
        }

        vector<int> order(n);
        vector<int> par(n, -1);
        int qh = 0, qt = 0;
        order[qt++] = 0;
        par[0] = -1;
        while (qh < qt) {
            int u = order[qh++];
            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];
                if (v != par[u]) {
                    par[v] = u;
                    order[qt++] = v;
                }
            }
        }

        vector<long long> sum(n);
        long long lo = 1, hi = total, ans = 0;
        while (lo <= hi) {
            long long mid = (lo + hi) / 2;
            for (int i = 0; i < n; i++) sum[i] = l[i];
            long long cnt = 0;
            for (int idx = n - 1; idx >= 0; idx--) {
                int u = order[idx];
                if (sum[u] >= mid) {
                    cnt++;
                    sum[u] = 0;
                }
                if (par[u] != -1) {
                    sum[par[u]] += sum[u];
                }
            }
            if (cnt >= (long long)k) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
