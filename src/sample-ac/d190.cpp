#include <cstdio>
#include <cstring>

const int MAXBUF = 1 << 20;
char buf[MAXBUF];
int p = MAXBUF;

inline char getc() {
    if (p == MAXBUF) {
        fread(buf, 1, MAXBUF, stdin);
        p = 0;
    }
    return buf[p++];
}

inline int readInt() {
    int x = 0;
    char c = getc();
    while (c < '0' || c > '9') c = getc();
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getc();
    }
    return x;
}

char outbuf[MAXBUF];
int outp = 0;

inline void putc(char c) {
    if (outp == MAXBUF) {
        fwrite(outbuf, 1, MAXBUF, stdout);
        outp = 0;
    }
    outbuf[outp++] = c;
}

inline void writeInt(int x) {
    char temp[12];
    int len = 0;
    if (x == 0) {
        putc('0');
        return;
    }
    while (x) {
        temp[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) putc(temp[len]);
}

int main() {
    int n;
    int count[100];
    while (true) {
        n = readInt();
        if (n == 0) break;
        
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; ++i) {
            int age = readInt();
            count[age]++;
        }
        
        bool first = true;
        for (int i = 1; i < 100; ++i) {
            for (int j = 0; j < count[i]; ++j) {
                if (!first) putc(' ');
                writeInt(i);
                first = false;
            }
        }
        putc('\n');
    }
    fwrite(outbuf, 1, outp, stdout);
    return 0;
}
