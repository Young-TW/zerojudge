#include <cstdio>

inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

inline void writeInt(long long x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    char buf[20];
    int len = 0;
    while (x > 0) {
        buf[len++] = x % 10 + '0';
        x /= 10;
    }
    while (len--) putchar(buf[len]);
}

inline void writeAns(long long R, long long S) {
    if (R == -1) {
        putchar('-');
        putchar('1');
    } else {
        writeInt(R);
        putchar(' ');
        writeInt(S);
    }
    putchar('\n');
}

int get_gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int inv_map[1000];

int main() {
    int t = readInt();
    while (t--) {
        int x = readInt();
        int y = readInt();
        int k = readInt();
        
        int g = get_gcd(x, y);
        int A = x / g;
        int B = y / g;
        
        for (int i = 1; i <= B; ++i) {
            int r_mod = (A * i) % B;
            inv_map[r_mod] = i;
        }
        
        for (int j = 0; j < k; ++j) {
            int a = readInt();
            if (a % g != 0) {
                writeAns(-1, -1);
                continue;
            }
            int C = a / g;
            int r_mod = C % B;
            int r = inv_map[r_mod];
            int s = (C - A * r) / B;
            if (s > 0) {
                writeAns(1000LL * r, 1000LL * s);
            } else {
                writeAns(-1, -1);
            }
        }
    }
    return 0;
}
