#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 3005;
const int W = (MAXN + 63) / 64;

unsigned long long A[MAXN][W], B[MAXN][W];
bool C[MAXN][MAXN];

char buf[1 << 25], *p1 = buf, *p2 = buf;
inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 1 << 25, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline int readInt() {
    int x = 0;
    char c = gc();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = gc();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int main() {
    int n = readInt();
    if (n == -1) return 0;
    
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if (readInt()) {
                A[i][j / 64] |= (1ULL << (j % 64));
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if (readInt()) {
                B[j][i / 64] |= (1ULL << (i % 64));
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            C[i][j] = readInt();
        }
    }
    
    for(int i = 0; i < n; ++i) {
        unsigned long long* Ai = A[i];
        for(int j = 0; j < n; ++j) {
            unsigned long long cnt = 0;
            unsigned long long* Bj = B[j];
            for(int k = 0; k < W; ++k) {
                cnt += __builtin_popcountll(Ai[k] & Bj[k]);
            }
            if ((cnt & 1) != C[i][j]) {
                printf("NO\n");
                return 0;
            }
        }
    }
    printf("YES\n");
    return 0;
}
