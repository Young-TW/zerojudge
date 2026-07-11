#pragma GCC optimize("O2")
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 10000000;
int phi[MAXN + 1];
long long sum_phi[MAXN + 1];

void init() {
    for (int i = 1; i <= MAXN; ++i) {
        phi[i] = i;
    }
    for (int i = 2; i <= MAXN; ++i) {
        if (phi[i] == i) {
            for (int j = i; j <= MAXN; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    sum_phi[0] = 0;
    for (int i = 1; i <= MAXN; ++i) {
        sum_phi[i] = sum_phi[i - 1] + phi[i];
    }
}

int main() {
    init();
    int T;
    if (scanf("%d", &T) != 1) return 0;
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        if (n > m) {
            swap(n, m);
        }
        long long ans = 0;
        for (int i = 1, j; i <= n; i = j + 1) {
            int a = n / i;
            int b = m / i;
            j = min(n / a, m / b);
            ans += (long long)a * b * (sum_phi[j] - sum_phi[i - 1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
