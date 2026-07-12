#include <vector>
#include <queue>
#include <functional>
#include <cstdio>

using namespace std;

char buf[1 << 20], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline bool readInt(int &x) {
    x = 0;
    char c = gc();
    while (c != EOF && (c < '0' || c > '9')) {
        c = gc();
    }
    if (c == EOF) return false;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
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

inline void writeInt(int x) {
    if (x == -1) {
        pc('-');
        pc('1');
    } else {
        if (x == 0) {
            pc('0');
        } else {
            char temp[12];
            int len = 0;
            while (x) {
                temp[len++] = x % 10 + '0';
                x /= 10;
            }
            while (len--) {
                pc(temp[len]);
            }
        }
    }
    pc('\n');
}

inline void flushOut() {
    if (op != obuf) {
        fwrite(obuf, 1, op - obuf, stdout);
    }
}

int main() {
    int n;
    while (readInt(n)) {
        vector<int> arr(n);
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < n; ++i) {
            readInt(arr[i]);
            if (arr[i] == 0) {
                pq.push(i);
            }
        }
        
        int m;
        readInt(m);
        for (int i = 0; i < m; ++i) {
            int op;
            readInt(op);
            if (op == 1) {
                int x;
                readInt(x);
                if (!pq.empty()) {
                    int idx = pq.top();
                    pq.pop();
                    arr[idx] = x;
                }
            } else if (op == 2) {
                int x;
                readInt(x);
                if (x >= 0 && x < n) {
                    if (arr[x] != 0) {
                        arr[x] = 0;
                        pq.push(x);
                    }
                }
            } else if (op == 3) {
                if (pq.empty()) {
                    writeInt(-1);
                } else {
                    writeInt(pq.top());
                }
            }
        }
    }
    flushOut();
    return 0;
}
