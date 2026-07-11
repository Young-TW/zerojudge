#include <cstdio>
#include <algorithm>
#include <functional>

const int MAXN = 1000005;
int arr[MAXN];

char buf[1 << 20];
int p = 0, size = 0;

inline char getc() {
    if (p == size) {
        size = fread(buf, 1, 1 << 20, stdin);
        p = 0;
        if (size == 0) return EOF;
    }
    return buf[p++];
}

inline bool readInt(int &x) {
    char c = getc();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == EOF) return false;
        c = getc();
    }
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = getc();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getc();
    }
    if (neg) x = -x;
    return true;
}

int main() {
    int N;
    if (!readInt(N)) return 0;
    for (int i = 0; i < N; ++i) {
        readInt(arr[i]);
    }
    int K;
    readInt(K);
    
    std::nth_element(arr, arr + K - 1, arr + N, std::greater<int>());
    printf("%d\n", arr[K - 1]);
    
    return 0;
}
