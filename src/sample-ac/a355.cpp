#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n, t;
    bool first_case = true;
    while (scanf("%d %d", &n, &t) == 2) {
        if (!first_case) printf("\n");
        first_case = false;
        const int MOD = 10000;
        int nb = n % MOD;
        for (int i = 0; i < t; i++) {
            int m;
            scanf("%d", &m);
            vector<int> s(m);
            for (int j = 0; j < m; j++) {
                scanf("%d", &s[j]);
            }
            // KMP failure function
            vector<int> fail(m, 0);
            for (int j = 1; j < m; j++) {
                int k = fail[j - 1];
                while (k > 0 && s[k] != s[j]) k = fail[k - 1];
                if (s[k] == s[j]) k++;
                fail[j] = k;
            }
            // Compute n^k mod 10000 for k = 1..m
            vector<int> pw(m + 1);
            pw[0] = 1 % MOD;
            for (int j = 1; j <= m; j++) {
                pw[j] = (pw[j - 1] * nb) % MOD;
            }
            // Collect border lengths and sum: m, fail[m-1], fail[fail[m-1]-1], ...
            int ans = pw[m];
            int b = fail[m - 1];
            while (b > 0) {
                ans = (ans + pw[b]) % MOD;
                b = fail[b - 1];
            }
            printf("%04d\n", ans);
        }
    }
    return 0;
}
