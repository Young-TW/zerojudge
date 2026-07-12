#include <cstdio>
#include <vector>
#include <stack>
#include <utility>

using namespace std;

const int EOF_FLAG = -1;

char buf[1 << 20], *p1 = buf, *p2 = buf;
inline int gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
        if (p1 == p2) return EOF_FLAG;
    }
    return *p1++;
}

inline bool read(long long &x) {
    x = 0;
    long long f = 1;
    int c = gc();
    while (c != EOF_FLAG && (c < '0' || c > '9')) {
        if (c == '-') f = -1;
        c = gc();
    }
    if (c == EOF_FLAG) return false;
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = gc();
    }
    x *= f;
    return true;
}

char obuf[1 << 20], *op = obuf;
inline void pc(char c) {
    if (op - obuf == (1 << 20)) {
        fwrite(obuf, 1, 1 << 20, stdout);
        op = obuf;
    }
    *op++ = c;
}

inline void write(long long x) {
    if (x < 0) {
        pc('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    pc(x % 10 + '0');
}

vector<vector<int>> adj;
vector<int> in, out;
vector<long long> bit;

int main() {
    long long n_ll, q_ll;
    while (read(n_ll)) {
        read(q_ll);
        int n = n_ll;
        int q = q_ll;
        
        adj.assign(n + 1, vector<int>());
        in.assign(n + 1, 0);
        out.assign(n + 1, 0);
        bit.assign(n + 2, 0);
        int timer = 0;
        
        for (int i = 1; i < n; ++i) {
            long long u_ll, v_ll;
            read(u_ll);
            read(v_ll);
            adj[u_ll].push_back(v_ll);
        }
        
        stack<pair<int, int>> st;
        st.push(make_pair(1, 0));
        while (!st.empty()) {
            int u = st.top().first;
            int state = st.top().second;
            st.pop();
            if (state == 0) {
                in[u] = ++timer;
                st.push(make_pair(u, 1));
                for (int i = (int)adj[u].size() - 1; i >= 0; --i) {
                    st.push(make_pair(adj[u][i], 0));
                }
            } else {
                out[u] = timer;
            }
        }
        
        while (q--) {
            long long op_ll;
            read(op_ll);
            int op = op_ll;
            if (op == 1) {
                long long u_ll, k_ll;
                read(u_ll);
                read(k_ll);
                int u = u_ll;
                long long k = k_ll;
                for (int idx = in[u]; idx <= n; idx += idx & -idx)
                    bit[idx] += k;
                for (int idx = out[u] + 1; idx <= n; idx += idx & -idx)
                    bit[idx] -= k;
            } else {
                long long u_ll;
                read(u_ll);
                int u = u_ll;
                long long res = 0;
                for (int idx = in[u]; idx > 0; idx -= idx & -idx)
                    res += bit[idx];
                write(res);
                pc('\n');
            }
        }
    }
    
    fwrite(obuf, 1, op - obuf, stdout);
    return 0;
}
