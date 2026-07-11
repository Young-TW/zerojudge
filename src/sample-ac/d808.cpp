#include <cstdio>
#include <cstring>

const int MAXN = 1000005;
int parent[MAXN];
int sz[MAXN];

const int MAXBUF = 1 << 20;
char buf[MAXBUF], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, MAXBUF, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline bool readInt(int &x) {
    char c = gc();
    while (c != EOF && (c < '0' || c > '9')) {
        c = gc();
    }
    if (c == EOF) return false;
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return true;
}

int find(int i) {
    int root = i;
    while (parent[root] != root) {
        root = parent[root];
    }
    while (parent[i] != root) {
        int next = parent[i];
        parent[i] = root;
        i = next;
    }
    return root;
}

void unite(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);
    if (rootI != rootJ) {
        if (sz[rootI] < sz[rootJ]) {
            parent[rootI] = rootJ;
            sz[rootJ] += sz[rootI];
        } else {
            parent[rootJ] = rootI;
            sz[rootI] += sz[rootJ];
        }
    }
}

int main() {
    int N;
    while (readInt(N)) {
        for (int i = 1; i <= N; ++i) {
            parent[i] = i;
            sz[i] = 1;
        }
        for (int i = 1; i <= N; ++i) {
            int x;
            if (readInt(x)) {
                unite(i, x);
            }
        }
        int max_sz = 0;
        int count = 0;
        for (int i = 1; i <= N; ++i) {
            if (parent[i] == i) {
                count++;
                if (sz[i] > max_sz) {
                    max_sz = sz[i];
                }
            }
        }
        printf("%d %d\n", count, max_sz);
    }
    return 0;
}
