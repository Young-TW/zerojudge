#include <vector>
#include <cstdio>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUFFER_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline int readInt() {
    int x = 0;
    char c = gc();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

char obuf[BUFFER_SIZE], *op = obuf;
inline void pc(char c) {
    if (op - obuf == BUFFER_SIZE) {
        fwrite(obuf, 1, BUFFER_SIZE, stdout);
        op = obuf;
    }
    *op++ = c;
}

inline void writeInt(int x) {
    if (x == 0) {
        pc('0');
        pc('\n');
        return;
    }
    char temp[12];
    int len = 0;
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) pc(temp[len]);
    pc('\n');
}

inline void flushOut() {
    if (op != obuf) {
        fwrite(obuf, 1, op - obuf, stdout);
    }
}

int main() {
    int n = readInt();
    int m = readInt();
    int r = readInt();

    vector<int> head(n + 1, -1);
    vector<int> to(2 * n);
    vector<int> nxt(2 * n);
    int edge_cnt = 0;

    for (int i = 0; i < n - 1; ++i) {
        int u = readInt();
        int v = readInt();
        to[edge_cnt] = v;
        nxt[edge_cnt] = head[u];
        head[u] = edge_cnt++;
        to[edge_cnt] = u;
        nxt[edge_cnt] = head[v];
        head[v] = edge_cnt++;
    }

    vector<int> parent(n + 1, 0);
    vector<int> order(n);
    int order_cnt = 0;
    vector<int> q_bfs(n);
    int head_bfs = 0, tail_bfs = 0;

    q_bfs[tail_bfs++] = r;
    parent[r] = -1;

    while (head_bfs < tail_bfs) {
        int u = q_bfs[head_bfs++];
        order[order_cnt++] = u;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (parent[v] == 0) {
                parent[v] = u;
                q_bfs[tail_bfs++] = v;
            }
        }
    }

    vector<int> sz(n + 1, 1);
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        if (parent[u] != -1) {
            sz[parent[u]] += sz[u];
        }
    }

    for (int i = 0; i < m; ++i) {
        int query = readInt();
        writeInt(sz[query]);
    }

    flushOut();

    return 0;
}
