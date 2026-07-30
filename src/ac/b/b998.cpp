#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <climits>
using namespace std;

namespace IO {
    const int IBUF = 1 << 16;
    char ib[IBUF]; int ip = 0, il = 0;
    inline int gc() {
        if (ip == il) {
            il = (int)fread(ib, 1, IBUF, stdin);
            ip = 0;
            if (il == 0) return -1;
        }
        return ib[ip++];
    }
    inline bool readInt(long long &x) {
        int c = gc();
        while (c != -1 && (c < '0' || c > '9')) c = gc();
        if (c == -1) return false;
        x = 0;
        while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
        return true;
    }
    const int OBUF = 1 << 20;
    char ob[OBUF]; int op = 0;
    inline void flush() { if (op) { fwrite(ob, 1, op, stdout); op = 0; } }
    inline void pc(char c) { if (op == OBUF) flush(); ob[op++] = c; }
    inline void writeNum(long long x) {
        if (x == 0) { pc('0'); return; }
        char tmp[24]; int n = 0;
        while (x > 0) { tmp[n++] = (char)('0' + x % 10); x /= 10; }
        while (n) pc(tmp[--n]);
    }
}

int main() {
    long long n, m, q, u, v, t;
    bool firstCase = true;
    while (IO::readInt(n)) {
        IO::readInt(m); IO::readInt(q); IO::readInt(u); IO::readInt(v); IO::readInt(t);
        vector<int> A((size_t)n);
        for (long long i = 0; i < n; i++) {
            long long x; IO::readInt(x);
            A[(size_t)i] = (int)x;
        }
        sort(A.begin(), A.end(), greater<int>());
        vector<int> B, C;
        B.reserve((size_t)m);
        C.reserve((size_t)m);
        size_t ha = 0, hb = 0, hc = 0;

        if (!firstCase) IO::pc('\n');
        firstCase = false;

        // 第一行：第 t, 2t, ... 秒被切斷的蚯蚓長度
        {
            bool firstNum = true;
            for (long long i = 1; i <= m; i++) {
                long long off = (i - 1) * q;
                long long cur = LLONG_MIN; int src = -1;
                if (ha < A.size() && A[ha] > cur) { cur = A[ha]; src = 0; }
                if (hb < B.size() && B[hb] > cur) { cur = B[hb]; src = 1; }
                if (hc < C.size() && C[hc] > cur) { cur = C[hc]; src = 2; }
                if (src == 0) ha++; else if (src == 1) hb++; else hc++;
                long long x = cur + off;
                if (i % t == 0) {
                    if (!firstNum) IO::pc(' ');
                    IO::writeNum(x);
                    firstNum = false;
                }
                long long l = (u * x) / v;
                long long r = x - l;
                long long boff = i * q;
                B.push_back((int)(l - boff));
                C.push_back((int)(r - boff));
            }
        }
        IO::pc('\n');

        // 第二行：m 秒後排名第 t, 2t, ... 的長度（三條單調隊列合併）
        {
            long long offm = m * q;
            long long rnk = 0;
            bool firstNum = true;
            while (ha < A.size() || hb < B.size() || hc < C.size()) {
                long long cur = LLONG_MIN; int src = -1;
                if (ha < A.size() && A[ha] > cur) { cur = A[ha]; src = 0; }
                if (hb < B.size() && B[hb] > cur) { cur = B[hb]; src = 1; }
                if (hc < C.size() && C[hc] > cur) { cur = C[hc]; src = 2; }
                if (src == 0) ha++; else if (src == 1) hb++; else hc++;
                rnk++;
                if (rnk % t == 0) {
                    if (!firstNum) IO::pc(' ');
                    IO::writeNum(cur + offm);
                    firstNum = false;
                }
            }
        }
        IO::pc('\n');
    }
    IO::flush();
    return 0;
}
