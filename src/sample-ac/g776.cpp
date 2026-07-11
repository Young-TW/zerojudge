#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE], *p1 = buf, *p2 = buf;

inline char getChar() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUFFER_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline bool readInt(int &x) {
    x = 0;
    char c = getChar();
    while (c < '0' || c > '9') {
        if (c == EOF) return false;
        c = getChar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getChar();
    }
    return true;
}

char obuf[BUFFER_SIZE], *op = obuf;
inline void putChar(char c) {
    if (op - obuf == BUFFER_SIZE) {
        fwrite(obuf, 1, BUFFER_SIZE, stdout);
        op = obuf;
    }
    *op++ = c;
}

inline void writeInt(int x) {
    if (x == 0) {
        putChar('0');
        putChar('\n');
        return;
    }
    char temp[12];
    int len = 0;
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) putChar(temp[len]);
    putChar('\n');
}

inline void flushOut() {
    if (op != obuf) fwrite(obuf, 1, op - obuf, stdout);
}

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        return r < other.r;
    }
};

class BIT {
    vector<int> tree;
    int n;
public:
    BIT(int size) : n(size), tree(size + 1, 0) {}
    void update(int i, int delta) {
        for (; i <= n; i += i & -i)
            tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }
};

int main() {
    int N;
    while (readInt(N)) {
        vector<int> m(N + 1);
        for (int i = 1; i <= N; ++i) {
            readInt(m[i]);
        }
        
        int Q;
        readInt(Q);
        vector<Query> queries(Q);
        for (int i = 0; i < Q; ++i) {
            readInt(queries[i].l);
            readInt(queries[i].r);
            queries[i].id = i;
        }
        
        sort(queries.begin(), queries.end());
        
        BIT bit(N);
        vector<int> last(N + 1, 0);
        vector<int> ans(Q);
        
        int q_idx = 0;
        for (int i = 1; i <= N; ++i) {
            if (last[m[i]] != 0) {
                bit.update(last[m[i]], -1);
            }
            bit.update(i, 1);
            last[m[i]] = i;
            
            while (q_idx < Q && queries[q_idx].r == i) {
                ans[queries[q_idx].id] = bit.query(queries[q_idx].r) - bit.query(queries[q_idx].l - 1);
                q_idx++;
            }
        }
        
        for (int i = 0; i < Q; ++i) {
            writeInt(ans[i]);
        }
    }
    flushOut();
    return 0;
}
