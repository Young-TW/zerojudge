#include <cstdio>
#include <cstring>

const int MAXN = 1000005;
int S[MAXN];
int dist[MAXN];
int q[MAXN];

inline bool readInt(int &x) {
    x = 0;
    int sign = 1;
    char c = getchar();
    while (c != EOF && (c < '0' || c > '9')) {
        if (c == '-') sign = -1;
        c = getchar();
    }
    if (c == EOF) return false;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    x *= sign;
    return true;
}

int main() {
    int n, P, L, R;
    while (readInt(n)) {
        readInt(P);
        readInt(L);
        readInt(R);
        for (int i = 0; i < n; ++i) {
            readInt(S[i]);
        }
        
        int head = 0, tail = 0;
        memset(dist, -1, sizeof(int) * n);
        
        dist[0] = 0;
        q[tail++] = 0;
        
        int ans = -1;
        while (head < tail) {
            int u = q[head++];
            if (u == P) {
                ans = dist[u];
                break;
            }
            
            int v1 = u - L;
            if (v1 >= 0) {
                int nxt = S[v1];
                if (nxt >= 0 && nxt < n && dist[nxt] == -1) {
                    dist[nxt] = dist[u] + 1;
                    q[tail++] = nxt;
                }
            }
            
            int v2 = u + R;
            if (v2 < n) {
                int nxt = S[v2];
                if (nxt >= 0 && nxt < n && dist[nxt] == -1) {
                    dist[nxt] = dist[u] + 1;
                    q[tail++] = nxt;
                }
            }
        }
        
        printf("%d\n", ans);
    }
    return 0;
}
