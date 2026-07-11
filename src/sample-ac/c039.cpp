#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1000001;
int memo[MAXN];

long long cycleLen(long long n) {
    if (n < MAXN && memo[n] != 0) return memo[n];
    long long next;
    if (n % 2 == 1) next = 3 * n + 1;
    else next = n / 2;
    long long len = 1 + cycleLen(next);
    if (n < MAXN) memo[n] = (int)len;
    return len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(memo, 0, sizeof(memo));
    memo[1] = 1;
    int i, j;
    while (cin >> i >> j) {
        int a = min(i, j);
        int b = max(i, j);
        int best = 0;
        for (int k = a; k <= b; k++) {
            int c = (int)cycleLen(k);
            if (c > best) best = c;
        }
        cout << i << " " << j << " " << best << "\n";
    }
    return 0;
}
