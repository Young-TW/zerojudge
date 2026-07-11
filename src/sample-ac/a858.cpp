#include <cstdio>
#include <vector>

using namespace std;

inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == EOF) return -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int main() {
    int N;
    while ((N = readInt()) != -1) {
        vector<long long> r(N, 0), b(N, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int c = readInt();
                if (c == 1) {
                    r[i]++;
                } else if (c == 2) {
                    b[i]++;
                }
            }
        }
        long long S = 0;
        for (int i = 0; i < N; ++i) {
            S += r[i] * (r[i] - 1) / 2 + b[i] * (b[i] - 1) / 2;
        }
        long long T = (long long)N * (N - 1) * (N - 2) / 6;
        printf("%lld\n", (S - T) / 2);
    }
    return 0;
}
