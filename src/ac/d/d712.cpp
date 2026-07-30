#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
int cyc[MAXN + 1];

int cycleLen(long long n) {
    // returns cycle length; memoize for n<=MAXN
    if (n <= MAXN && cyc[n]) return cyc[n];
    int res;
    if (n == 1) res = 1;
    else if (n & 1) res = 1 + cycleLen(3 * n + 1);
    else res = 1 + cycleLen(n / 2);
    if (n <= MAXN) cyc[n] = res;
    return res;
}

short sp[21][MAXN + 1];
int LOG[MAXN + 1];

int main(){
    for (int i = 1; i <= MAXN; i++) cyc[i] = cycleLen(i);
    LOG[1] = 0;
    for (int i = 2; i <= MAXN; i++) LOG[i] = LOG[i/2] + 1;
    for (int i = 1; i <= MAXN; i++) sp[0][i] = cyc[i];
    for (int k = 1; (1<<k) <= MAXN; k++)
        for (int i = 1; i + (1<<k) - 1 <= MAXN; i++)
            sp[k][i] = max(sp[k-1][i], sp[k-1][i + (1<<(k-1))]);
    long long a, b;
    while (scanf("%lld %lld", &a, &b) == 2) {
        long long lo = min(a,b), hi = max(a,b);
        int k = LOG[hi - lo + 1];
        int ans = max(sp[k][lo], sp[k][hi - (1<<k) + 1]);
        printf("%lld %lld %d\n", a, b, ans);
    }
    return 0;
}
