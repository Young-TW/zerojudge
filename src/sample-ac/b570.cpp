#include <cstdio>

const int MAX_M = 1000005;

int edges_u[MAX_M];
int edges_v[MAX_M];
int destroyed[MAX_M];
bool is_destroyed[MAX_M];
int ans[MAX_M];
int parent[10005];
int rank_[10005];

const int MAX_BUF = 1 << 20;
char in_buf[MAX_BUF];
int in_p = 0, in_sz = 0;

inline char gc() {
    if (in_p == in_sz) {
        in_sz = fread(in_buf, 1, MAX_BUF, stdin);
        in_p = 0;
        if (in_sz == 0) return EOF;
    }
    return in_buf[in_p++];
}

inline bool readInt(int &x) {
    x = 0;
    char c = gc();
    while (c != EOF && (c < '0' || c > '9')) c = gc();
    if (c == EOF) return false;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return true;
}

char out_buf[MAX_BUF];
int out_p = 0;

inline void flush_out() {
    if (out_p) {
        fwrite(out_buf, 1, out_p, stdout);
        out_p = 0;
    }
}

inline void writeInt(int x) {
    if (out_p > MAX_BUF - 15) {
        flush_out();
    }
    if (x == 0) {
        out_buf[out_p++] = '0';
        out_buf[out_p++] = '\n';
        return;
    }
    char temp[12];
    int len = 0;
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) {
        out_buf[out_p++] = temp[len];
    }
    out_buf[out_p++] = '\n';
}

void init_dsu(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank_[i] = 0;
    }
}

int find(int x) {
    return parent[x] == x ? x : (parent[x] = find(parent[x]));
}

bool unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx == ry) return false;
    if (rank_[rx] < rank_[ry]) {
        parent[rx] = ry;
    } else if (rank_[rx] > rank_[ry]) {
        parent[ry] = rx;
    } else {
        parent[ry] = rx;
        rank_[rx]++;
    }
    return true;
}

int main() {
    int n, m;
    while (readInt(n) && readInt(m)) {
        for (int i = 1; i <= m; i++) {
            readInt(edges_u[i]);
            readInt(edges_v[i]);
            is_destroyed[i] = false;
        }
        int q;
        readInt(q);
        for (int i = 0; i < q; i++) {
            readInt(destroyed[i]);
            is_destroyed[destroyed[i]] = true;
        }
        
        init_dsu(n);
        int components = n;
        
        for (int i = 1; i <= m; i++) {
            if (!is_destroyed[i]) {
                if (unite(edges_u[i], edges_v[i])) {
                    components--;
                }
            }
        }
        
        ans[q] = components;
        for (int i = q - 1; i >= 0; i--) {
            int edge_idx = destroyed[i];
            if (unite(edges_u[edge_idx], edges_v[edge_idx])) {
                components--;
            }
            ans[i] = components;
        }
        
        for (int i = 1; i <= q; i++) {
            writeInt(ans[i]);
        }
    }
    flush_out();
    return 0;
}
