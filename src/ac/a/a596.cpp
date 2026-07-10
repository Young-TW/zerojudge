#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MOD = 12345;
const int MAXV = 30002;

int bitCnt[MAXV];
int bitUp[MAXV];
int bitDn[MAXV];

int a[1505];

inline void addMod(int* bit, int idx, int val) {
    for (; idx < MAXV; idx += idx & (-idx))
        bit[idx] = (bit[idx] + val) % MOD;
}

inline int queryMod(int* bit, int idx) {
    int s = 0;
    for (; idx > 0; idx -= idx & (-idx))
        s = (s + bit[idx]) % MOD;
    return s;
}

inline void addRaw(int* bit, int idx, int val) {
    for (; idx < MAXV; idx += idx & (-idx))
        bit[idx] += val;
}

inline int queryRaw(int* bit, int idx) {
    int s = 0;
    for (; idx > 0; idx -= idx & (-idx))
        s += bit[idx];
    return s;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);

        memset(bitCnt, 0, sizeof(bitCnt));
        memset(bitUp, 0, sizeof(bitUp));
        memset(bitDn, 0, sizeof(bitDn));

        int ans = 0;
        int equalPairs = 0;
        int totalSup = 0;

        for (int i = 0; i < n; i++) {
            int v = a[i] + 1;
            int less_cnt = queryRaw(bitCnt, v - 1);
            int le_cnt = queryRaw(bitCnt, v);
            int eq_cnt = le_cnt - less_cnt;
            int greater_cnt = i - le_cnt;
            equalPairs += eq_cnt;

            int less_sumDn = queryMod(bitDn, v - 1);
            int greater_sumUp = ((totalSup - queryMod(bitUp, v)) % MOD + MOD) % MOD;

            int Sup = (less_cnt + less_sumDn) % MOD;
            int Sdn = (greater_cnt % MOD + greater_sumUp) % MOD;

            ans = (ans + Sup + Sdn) % MOD;

            addRaw(bitCnt, v, 1);
            addMod(bitUp, v, Sup);
            addMod(bitDn, v, Sdn);
            totalSup = (totalSup + Sup) % MOD;
        }

        long long totalPairs = (long long)n * (n - 1) / 2;
        long long diffPairs = totalPairs - equalPairs;
        int diffMod = (int)(diffPairs % MOD);
        ans = ((ans - diffMod) % MOD + MOD) % MOD;

        printf("%d\n", ans);
    }
    return 0;
}
