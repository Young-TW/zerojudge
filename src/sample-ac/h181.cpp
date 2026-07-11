#include <cstdio>
#include <algorithm>

int arr[1000005];

char buf[1024];
int p = 0, len = 0;
inline char getChar() {
    if (p == len) {
        len = fread(buf, 1, 1024, stdin);
        p = 0;
        if (len == 0) return EOF;
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

int main() {
    int N = readInt();
    for (int i = 0; i < N; ++i) {
        arr[i] = readInt();
    }
    int K = readInt();
    
    std::nth_element(arr, arr + K - 1, arr + N, [](int a, int b){ return a > b; });
    
    printf("%d\n", arr[K - 1]);
    return 0;
}
