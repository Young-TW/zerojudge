#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int BUFFER_SIZE = 1 << 20;
char buf[BUFFER_SIZE], *p1 = buf, *p2 = buf;

inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUFFER_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline bool readInt(int &x) {
    char c = gc();
    while (c != EOF && (c < '0' || c > '9') && c != '-') c = gc();
    if (c == EOF) return false;
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = gc();
    }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    if (neg) x = -x;
    return true;
}

int main() {
    vector<int> xs;
    vector<int> ys;
    xs.reserve(1000005);
    ys.reserve(1000005);
    
    int T;
    while (readInt(T)) {
        while (T--) {
            int N;
            readInt(N);
            xs.resize(N);
            ys.resize(N);
            for (int i = 0; i < N; ++i) {
                readInt(xs[i]);
                readInt(ys[i]);
            }
            
            sort(xs.begin(), xs.end());
            sort(ys.begin(), ys.end());
            
            long long ans = 0;
            for (int i = 0; i < N / 2; ++i) {
                ans += (long long)xs[N - 1 - i] - xs[i];
                ans += (long long)ys[N - 1 - i] - ys[i];
            }
            
            printf("%lld\n", ans);
        }
    }
    return 0;
}
