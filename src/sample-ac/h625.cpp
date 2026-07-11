#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE], *p1 = buf, *p2 = buf;

inline char gc() {
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

inline int read() {
    int x = 0;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == EOF) return -1;
        ch = gc();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = gc();
    }
    return x;
}

int main() {
    int N;
    while ((N = read()) != -1) {
        vector<vector<int>> P(N + 1);
        vector<vector<int>> L(N + 1);
        vector<int> last_occurrence(N + 1, 0);
        vector<bool> in_P(N + 1, false);

        for (int i = 1; i <= N; ++i) {
            int M = read();
            vector<int> temp(M);
            for (int j = 0; j < M; ++j) {
                temp[j] = read();
            }
            sort(temp.begin(), temp.end());
            temp.erase(unique(temp.begin(), temp.end()), temp.end());
            P[i] = temp;
            for (int k : P[i]) {
                L[k].push_back(i);
            }
        }

        for (int i = N; i >= 1; --i) {
            for (int k : P[i]) {
                if (last_occurrence[k] == 0) {
                    last_occurrence[k] = i;
                }
            }
        }

        long long ans = 0;
        for (int i = 1; i <= N; ++i) {
            for (int k : P[i]) {
                in_P[k] = true;
            }
            for (int k : P[i]) {
                if (last_occurrence[k] == i) {
                    for (int j : L[k]) {
                        if (in_P[j]) {
                            ans++;
                        }
                    }
                }
            }
            for (int k : P[i]) {
                in_P[k] = false;
            }
        }

        printf("%lld\n", ans);
    }
    return 0;
}
