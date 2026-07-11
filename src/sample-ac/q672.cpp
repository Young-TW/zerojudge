#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE];
int buf_pos = 0, buf_len = 0;

inline int get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUF_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline bool readInt(int &x) {
    int c = get_char();
    while (c != EOF && (c < '0' || c > '9') && c != '-') c = get_char();
    if (c == EOF) return false;
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = get_char();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    if (neg) x = -x;
    return true;
}

struct Edge {
    int u, v, c;
    bool operator<(const Edge& other) const {
        return c < other.c;
    }
};

const int MAXN = 200005;
int parent[MAXN];
int rnk[MAXN];

int find(int i) {
    return parent[i] == i ? i : (parent[i] = find(parent[i]));
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        if (rnk[root_i] < rnk[root_j]) {
            parent[root_i] = root_j;
        } else if (rnk[root_i] > rnk[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rnk[root_i]++;
        }
    }
}

int main() {
    int N, M, K;
    while (readInt(N)) {
        readInt(M);
        readInt(K);
        
        for (int i = 1; i <= N; ++i) {
            parent[i] = i;
            rnk[i] = 0;
        }
        
        int first_giant = 0;
        if (K > 0) {
            readInt(first_giant);
            for (int i = 1; i < K; ++i) {
                int giant;
                readInt(giant);
                unite(first_giant, giant);
            }
        }
        
        vector<Edge> edges;
        edges.reserve(M);
        for (int i = 0; i < M; ++i) {
            Edge e;
            readInt(e.u);
            readInt(e.v);
            readInt(e.c);
            edges.push_back(e);
        }
        
        sort(edges.begin(), edges.end());
        
        long long total_cost = 0;
        for (int i = 0; i < M; ++i) {
            int u = edges[i].u;
            int v = edges[i].v;
            if (find(u) != find(v)) {
                unite(u, v);
                total_cost += edges[i].c;
            }
        }
        
        printf("%lld\n", total_cost);
    }
    return 0;
}
