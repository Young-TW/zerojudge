#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = 1000005;

struct Edge {
    int to;
    long long weight;
    int next;
};

Edge edges[MAXN * 2];
int head[MAXN];
int edgeCount = 0;

void addEdge(int u, int v, long long w) {
    edges[++edgeCount] = {v, w, head[u]};
    head[u] = edgeCount;
}

int parent[MAXN];
int order[MAXN];
int orderCount = 0;
int sz[MAXN];
int q[MAXN];

char buf[1 << 20];
int buf_pos = 0;
int buf_len = 0;

inline char get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, sizeof(buf), stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline bool readInt(int &x) {
    char c = get_char();
    while (c != EOF && (c < '0' || c > '9')) {
        c = get_char();
    }
    if (c == EOF) return false;
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return true;
}

inline long long readLong() {
    long long x = 0;
    char c = get_char();
    while (c != EOF && (c < '0' || c > '9')) {
        c = get_char();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

int main() {
    int n;
    while (readInt(n)) {
        edgeCount = 0;
        orderCount = 0;
        for (int i = 1; i <= n; ++i) {
            head[i] = 0;
            parent[i] = 0;
            sz[i] = 1;
        }
        
        for (int i = 1; i < n; ++i) {
            int u, v;
            readInt(u);
            readInt(v);
            long long c = readLong();
            addEdge(u, v, c);
            addEdge(v, u, c);
        }
        
        int q_head = 0, q_tail = 0;
        q[q_tail++] = 1;
        parent[1] = -1;
        
        while (q_head < q_tail) {
            int u = q[q_head++];
            order[orderCount++] = u;
            
            for (int i = head[u]; i != 0; i = edges[i].next) {
                int v = edges[i].to;
                if (parent[v] == 0) {
                    parent[v] = u;
                    q[q_tail++] = v;
                }
            }
        }
        
        long long totalCost = 0;
        
        for (int i = orderCount - 1; i >= 0; --i) {
            int u = order[i];
            if (u == 1) continue;
            
            int p = parent[u];
            sz[p] += sz[u];
            
            long long w = 0;
            for (int j = head[u]; j != 0; j = edges[j].next) {
                if (edges[j].to == p) {
                    w = edges[j].weight;
                    break;
                }
            }
            
            long long diff = 2LL * sz[u] - n;
            if (diff < 0) diff = -diff;
            totalCost += w * diff;
        }
        
        printf("%lld\n", totalCost);
    }
    
    return 0;
}
