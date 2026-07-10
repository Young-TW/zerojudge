#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
using namespace std;

static long long isqrt_ps(long long n) {
    if (n < 0) return -1;
    long long x = (long long)sqrtl((long double)n);
    while (x > 0 && x * x > n) --x;
    while ((x + 1) * (x + 1) <= n) ++x;
    return (x * x == n) ? x : -1;
}

static long long gcd_ll(long long a, long long b) {
    while (b) { long long t = a % b; a = b; b = t; }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<long long> s(N);
        vector<int> oddIdx, evenIdx;
        for (int i = 0; i < N; ++i) {
            cin >> s[i];
            if (s[i] % 2 == 0) evenIdx.push_back(i);
            else oddIdx.push_back(i);
        }

        int L = (int)oddIdx.size();
        int R = (int)evenIdx.size();
        vector<vector<int>> adj(L);
        for (int i = 0; i < L; ++i) {
            long long a = s[oddIdx[i]];
            for (int j = 0; j < R; ++j) {
                long long b = s[evenIdx[j]];
                if (gcd_ll(a, b) != 1) continue;
                long long sum = a * a + b * b;
                if (isqrt_ps(sum) != -1) adj[i].push_back(j);
            }
        }

        vector<int> matchR(R, -1);
        int ans = 0;
        for (int u = 0; u < L; ++u) {
            vector<char> seen(R, 0);
            function<bool(int)> dfs = [&](int u) -> bool {
                for (int v : adj[u]) {
                    if (seen[v]) continue;
                    seen[v] = 1;
                    if (matchR[v] == -1 || dfs(matchR[v])) {
                        matchR[v] = u;
                        return true;
                    }
                }
                return false;
            };
            if (dfs(u)) ++ans;
        }
        cout << ans << "\n";
    }
    return 0;
}
