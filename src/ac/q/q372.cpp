#include <cstdio>

const int MAXN = 1000005;
struct Prefix {
    long long s1;
    unsigned long long s2;
} prefix[MAXN];

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE], *p1 = buf, *p2 = buf;

inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUFFER_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline long long readInt() {
    long long x = 0;
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

char obuf[BUFFER_SIZE];
int pos = 0;

inline void pc(char c) {
    if (pos == BUFFER_SIZE) {
        fwrite(obuf, 1, BUFFER_SIZE, stdout);
        pos = 0;
    }
    obuf[pos++] = c;
}

inline void writeInt(long long x) {
    if (x == 0) {
        pc('0');
        return;
    }
    char temp[20];
    int len = 0;
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) {
        pc(temp[len]);
    }
}

int main() {
    while (true) {
        long long N = readInt();
        if (N == -1) break;
        long long Q = readInt();
        
        prefix[0].s1 = 0;
        prefix[0].s2 = 0;
        for (int i = 1; i <= N; ++i) {
            long long a = readInt();
            prefix[i].s1 = prefix[i - 1].s1 + a;
            prefix[i].s2 = prefix[i - 1].s2 + (unsigned long long)a * (unsigned long long)a;
        }
        
        for (int i = 0; i < Q; ++i) {
            long long l = readInt();
            long long r = readInt();
            
            long long len = r - l + 1;
            long long S1 = prefix[r].s1 - prefix[l - 1].s1;
            unsigned long long S2 = prefix[r].s2 - prefix[l - 1].s2;
            
            __int128 num = (__int128)S2 * len - (__int128)S1 * S1;
            __int128 den = (__int128)len * len;
            
            __int128 ans = (num * 2 + den) / (2 * den);
            writeInt((long long)ans);
            pc('\n');
        }
    }
    
    if (pos > 0) {
        fwrite(obuf, 1, pos, stdout);
    }
    
    return 0;
}
