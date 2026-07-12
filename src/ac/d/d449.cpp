#include <cstdio>

const int MAX_SIZE = 1010050;
const int MAXN = 10005;
const int BUF_SIZE = 1 << 22;

int fa[MAX_SIZE];
int id[MAXN];
int tag[MAX_SIZE];
int rank[MAX_SIZE];
int cur_tag = 0;

int find(int x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

void unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx != ry) {
        if (rank[rx] < rank[ry]) {
            fa[rx] = ry;
        } else if (rank[rx] > rank[ry]) {
            fa[ry] = rx;
        } else {
            fa[rx] = ry;
            rank[ry]++;
        }
    }
}

char buf[BUF_SIZE], *p1 = buf, *p2 = buf;
inline int gc() {
    if (p1 == p2) {
        p1 = buf;
        p2 = buf + fread(buf, 1, BUF_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return (unsigned char)*p1++;
}

inline bool readInt(int &x) {
    x = 0;
    int c = gc();
    while (c < '0' || c > '9') {
        if (c == EOF) return false;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return true;
}

int main() {
    int n, m;
    while (readInt(n)) {
        if (!readInt(m)) break;
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
            id[i] = i;
            rank[i] = 0;
        }
        int cnt = 0;
        for (int i = 0; i < m; ++i) {
            int op;
            readInt(op);
            if (op == 1) {
                int x, y;
                readInt(x);
                readInt(y);
                unite(id[x], id[y]);
            } else if (op == 2) {
                int x;
                readInt(x);
                cnt++;
                fa[n + cnt] = n + cnt;
                id[x] = n + cnt;
                rank[n + cnt] = 0;
            }
        }
        
        int ans = 0;
        cur_tag++;
        for (int i = 1; i <= n; ++i) {
            int root = find(id[i]);
            if (tag[root] != cur_tag) {
                tag[root] = cur_tag;
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
