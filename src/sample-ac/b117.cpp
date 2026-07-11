#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAXM = 1000005;
const int INF = 2000000005;

int head1[MAXM], head2[MAXM];
int to1[MAXM], to2[MAXM];
int val1[MAXM], val2[MAXM];
int nxt1[MAXM], nxt2[MAXM];
int edge_cnt;

int dist1[MAXM], dist2[MAXM];

struct Edge {
    int to, val;
    bool operator<(const Edge& other) const {
        return val > other.val;
    }
};

inline char readChar() {
    static char buf[1 << 16], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 1 << 16, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline bool readInt(int &x) {
    char c = readChar();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return false;
        c = readChar();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = readChar();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = readChar();
    }
    if (neg) x = -x;
    return true;
}

void dijkstra(int head[], int to[], int val[], int nxt[], int dist[], int M) {
    for (int i = 1; i <= M; i++) dist[i] = INF;
    dist[1] = 0;
    priority_queue<Edge> pq;
    pq.push({1, 0});
    while (!pq.empty()) {
        Edge curr = pq.top();
        pq.pop();
        int u = curr.to;
        int d = curr.val;
        if (d > dist[u]) continue;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = val[i];
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({v, dist[v]});
            }
        }
    }
}

int main() {
    int M, N;
    while (readInt(M)) {
        if (!readInt(N)) break;
        edge_cnt = 0;
        memset(head1, 0, sizeof(int) * (M + 1));
        memset(head2, 0, sizeof(int) * (M + 1));
        
        for (int i = 0; i < N; i++) {
            int p, q, r;
            readInt(p);
            readInt(q);
            readInt(r);
            edge_cnt++;
            to1[edge_cnt] = q; val1[edge_cnt] = r; nxt1[edge_cnt] = head1[p]; head1[p] = edge_cnt;
            to2[edge_cnt] = p; val2[edge_cnt] = r; nxt2[edge_cnt] = head2[q]; head2[q] = edge_cnt;
        }
        
        dijkstra(head1, to1, val1, nxt1, dist1, M);
        dijkstra(head2, to2, val2, nxt2, dist2, M);
        
        long long ans = 0;
        bool possible = true;
        for (int i = 2; i <= M; i++) {
            if (dist1[i] == INF || dist2[i] == INF) {
                possible = false;
                break;
            }
            ans += dist1[i] + dist2[i];
        }
        
        if (possible) {
            printf("%lld\n", ans);
        } else {
            printf("0\n");
        }
    }
    return 0;
}
