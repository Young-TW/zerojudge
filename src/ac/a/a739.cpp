#include <cstdio>
#include <cstring>

const int MAXN = 2000005;
int head[MAXN];
int nxt[MAXN];
int cost[MAXN];
int tin[MAXN];
int tout[MAXN];
int depth[MAXN];
long long dist[MAXN];
int ptr[MAXN];
int stk[MAXN];

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE];
int buf_pos = 0, buf_len = 0;

inline char get_char() {
    if (buf_pos == buf_len) {
        buf_len = fread(buf, 1, BUFFER_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline int readInt() {
    int x = 0;
    char c = get_char();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = get_char();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

char out_buf[BUFFER_SIZE];
int out_pos = 0;

inline void writeInt(long long x) {
    if (x == 0) {
        out_buf[out_pos++] = '0';
    } else {
        char temp[20];
        int len = 0;
        while (x > 0) {
            temp[len++] = x % 10 + '0';
            x /= 10;
        }
        while (len > 0) {
            out_buf[out_pos++] = temp[--len];
        }
    }
    out_buf[out_pos++] = '\n';
    if (out_pos >= BUFFER_SIZE - 20) {
        fwrite(out_buf, 1, out_pos, stdout);
        out_pos = 0;
    }
}

inline void flush_out() {
    if (out_pos > 0) {
        fwrite(out_buf, 1, out_pos, stdout);
    }
}

int main() {
    int n;
    while ((n = readInt()) != -1) {
        for (int i = 1; i <= n; ++i) {
            head[i] = 0;
        }
        for (int i = 2; i <= n; ++i) {
            int p = readInt();
            int c = readInt();
            nxt[i] = head[p];
            head[p] = i;
            cost[i] = c;
        }
        
        for (int i = 1; i <= n; ++i) {
            ptr[i] = head[i];
        }
        
        int top = 0;
        stk[top++] = 1;
        tin[1] = 1;
        depth[1] = 0;
        dist[1] = 0;
        int timer = 1;
        
        while (top > 0) {
            int u = stk[top - 1];
            int v = ptr[u];
            if (v != 0) {
                ptr[u] = nxt[v];
                stk[top++] = v;
                tin[v] = ++timer;
                depth[v] = depth[u] + 1;
                dist[v] = dist[u] + cost[v];
            } else {
                tout[u] = ++timer;
                top--;
            }
        }
        
        int q = readInt();
        long long x = 0;
        
        for (int i = 0; i < q; ++i) {
            int a = readInt();
            int b = readInt();
            
            if (a != b && tin[a] <= tin[b] && tout[a] >= tout[b]) {
                long long ans = dist[b] - dist[a] + (long long)(depth[b] - depth[a]) * x;
                writeInt(ans);
            } else {
                x++;
            }
        }
    }
    flush_out();
    return 0;
}
