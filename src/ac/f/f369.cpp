#include <cstdio>
#include <cstring>
#include <algorithm>

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE];
int p = 0;
int buf_size = 0;

inline char getChar() {
    if (p == buf_size) {
        buf_size = fread(buf, 1, BUF_SIZE, stdin);
        p = 0;
        if (buf_size == 0) return EOF;
    }
    return buf[p++];
}

inline int readInt() {
    int x = 0;
    char c = getChar();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return 0;
        c = getChar();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = getChar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getChar();
    }
    return neg ? -x : x;
}

char out_buf[BUF_SIZE];
int out_p = 0;

inline void writeInt(__int128 x) {
    if (out_p > BUF_SIZE - 100) {
        fwrite(out_buf, 1, out_p, stdout);
        out_p = 0;
    }
    if (x == 0) {
        out_buf[out_p++] = '0';
        out_buf[out_p++] = '\n';
        return;
    }
    if (x < 0) {
        out_buf[out_p++] = '-';
        x = -x;
    }
    char temp[40];
    int t = 0;
    while (x > 0) {
        temp[t++] = '0' + (int)(x % 10);
        x /= 10;
    }
    while (t > 0) {
        out_buf[out_p++] = temp[--t];
    }
    out_buf[out_p++] = '\n';
}

long long gcd_ll(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        a %= b;
        long long temp = a;
        a = b;
        b = temp;
    }
    return a;
}

__int128 gcd128(__int128 a, __int128 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        a %= b;
        __int128 temp = a;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    int t = readInt();
    while (t--) {
        int n = readInt();
        long long x[5], y[5];
        for (int i = 0; i <= n; ++i) {
            x[i] = readInt();
        }
        for (int i = 0; i <= n; ++i) {
            y[i] = readInt();
        }
        long long k = readInt();
        
        __int128 sum_num = 0;
        __int128 sum_den = 1;
        
        for (int i = 0; i <= n; ++i) {
            long long num = y[i];
            long long den = 1;
            for (int j = 0; j <= n; ++j) {
                if (i == j) continue;
                num *= (k - x[j]);
                den *= (x[i] - x[j]);
                long long g = gcd_ll(num, den);
                if (g > 1) {
                    num /= g;
                    den /= g;
                }
            }
            
            __int128 g = gcd128(sum_den, den);
            __int128 new_den = sum_den / g * den;
            __int128 new_num = sum_num * (den / g) + (__int128)num * (sum_den / g);
            
            sum_den = new_den;
            sum_num = new_num;
            
            g = gcd128(sum_num, sum_den);
            if (g > 1) {
                sum_num /= g;
                sum_den /= g;
            }
        }
        
        if (sum_den < 0) {
            sum_num = -sum_num;
            sum_den = -sum_den;
        }
        
        __int128 ans = sum_num / (100 * sum_den);
        writeInt(ans);
    }
    
    fwrite(out_buf, 1, out_p, stdout);
    return 0;
}
