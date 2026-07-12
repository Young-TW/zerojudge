#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_D = 40005;
bool dp[MAX_D + 1];

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

inline void writeYes() {
    putChar('Y'); putChar('E'); putChar('S'); putChar('\n');
}

inline void writeNo() {
    putChar('N'); putChar('O'); putChar('\n');
}

inline void flushOut() {
    if (op != obuf) fwrite(obuf, 1, op - obuf, stdout);
}

int gcd(int a, int b) {
    while (b) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    int N, M, Q;
    while (readInt(N)) {
        if (!readInt(M) || !readInt(Q)) break;
        
        int g = gcd(N, M);
        int n_prime = N / g;
        int m_prime = M / g;
        
        memset(dp, 0, sizeof(dp));
        dp[0] = true;
        for (int i = 1; i <= MAX_D; ++i) {
            if (i >= n_prime && dp[i - n_prime]) dp[i] = true;
            if (i >= m_prime && dp[i - m_prime]) dp[i] = true;
        }
        
        for (int i = 0; i < Q; ++i) {
            int D;
            if (!readInt(D)) break;
            if (D % g != 0) {
                writeNo();
            } else {
                int d_prime = D / g;
                if (d_prime > MAX_D) {
                    writeYes();
                } else {
                    if (dp[d_prime]) {
                        writeYes();
                    } else {
                        writeNo();
                    }
                }
            }
        }
    }
    flushOut();
    return 0;
}
