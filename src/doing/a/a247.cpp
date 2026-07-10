#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;
bool used[MAXN];

int gcd(int a, int b) { while (b) { int t = a % b; a = b; b = t; } return a; }

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        memset(used, 0, sizeof(bool) * (N + 1));
        long long cnt = 0;
        for (int m = 2; (long long)m * m + 1 <= N; m++) {
            for (int n = 1; n < m; n++) {
                long long c = (long long)m * m + (long long)n * n;
                if (c > N) break;
                if (((m - n) & 1) == 0) continue;
                if (gcd(m, n) != 1) continue;
                long long a = (long long)m * m - (long long)n * n;
                long long b = 2LL * m * n;
                cnt++;
                int ai = (int)a, bi = (int)b, ci = (int)c;
                for (int k = 1; (long long)k * ci <= N; k++) {
                    used[k * ai] = true;
                    used[k * bi] = true;
                    used[k * ci] = true;
                }
            }
        }
        long long unused = 0;
        for (int i = 1; i <= N; i++) if (!used[i]) unused++;
        printf("%lld %lld\n", cnt, unused);
    }
    return 0;
}
