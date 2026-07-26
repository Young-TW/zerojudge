#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int p, q, a, n;
int ans;

int gcd_int(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void dfs(int start_d, int rem_p, int rem_q, int prod, int depth) {
    if (rem_p == 0) {
        ans++;
        return;
    }
    if (depth == n) return;

    long long min_d = max((long long)start_d, ((long long)rem_q + rem_p - 1) / rem_p);
    long long max_d_val = (long long)a / prod;

    if (min_d > max_d_val) return;

    for (long long d = min_d; d <= max_d_val; d++) {
        long long next_prod = prod * d;
        if (next_prod > a) break;

        long long new_q = (long long)rem_q * d;
        long long new_p = (long long)rem_p * d - rem_q;

        if (new_p < 0) continue;

        long long common = gcd_int(new_p, new_q);
        long long np = new_p / common;
        long long nq = new_q / common;

        if (np > 800 || nq > 800) continue;

        dfs(d, np, nq, next_prod, depth + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> p >> q >> a >> n && (p || q || a || n)) {
        ans = 0;
        int common = gcd_int(p, q);
        p /= common;
        q /= common;
        dfs(1, p, q, 1, 0);
        cout << ans << "\n";
    }

    return 0;
}
