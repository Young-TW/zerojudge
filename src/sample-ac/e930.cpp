#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int INF = 0x3f3f3f3f;

int dp[100005];
int next_dp[100005];

int U[1000005];
int V[1000005];
int W[1000005];

char buffer[1 << 16];
int buffer_pos = 0;
int buffer_len = 0;

inline char get_char() {
    if (buffer_pos == buffer_len) {
        buffer_len = fread(buffer, 1, 1 << 16, stdin);
        buffer_pos = 0;
        if (buffer_len == 0) return EOF;
    }
    return buffer[buffer_pos++];
}

inline int read_int() {
    char c = get_char();
    while (c != EOF && (c < '0' || c > '9')) {
        c = get_char();
    }
    if (c == EOF) return -1;
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

int main() {
    int n, m, k;
    while (true) {
        n = read_int();
        if (n == -1) break;
        m = read_int();
        k = read_int();

        for (int i = 0; i < m; ++i) {
            U[i] = read_int();
            V[i] = read_int();
            W[i] = read_int();
        }

        memset(dp, 0x3f, sizeof(int) * n);
        dp[0] = 0;

        int ans = dp[n - 1];

        for (int i = 1; i <= k; ++i) {
            memset(next_dp, 0x3f, sizeof(int) * n);
            bool updated = false;
            for (int j = 0; j < m; ++j) {
                int u = U[j];
                if (dp[u] != INF) {
                    int v = V[j];
                    int new_w = dp[u] + W[j];
                    if (new_w < next_dp[v]) {
                        next_dp[v] = new_w;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
            swap(dp, next_dp);
            if (dp[n - 1] < ans) {
                ans = dp[n - 1];
            }
        }

        if (ans == INF) {
            printf("impossible\n");
        } else {
            printf("%d\n", ans);
        }
    }

    return 0;
}
