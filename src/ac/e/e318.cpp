#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
long long d, k;
vector<long long> x, s;

const long long INF = 1e18;

bool check(long long g) {
    long long L = max(1LL, d - g);
    long long R = d + g;
    vector<long long> dp(n + 1, -INF);
    dp[0] = 0;
    
    int head = 0, tail = 0;
    int ptr = 0;
    vector<int> q(n + 1);
    
    for (int i = 1; i <= n; ++i) {
        while (ptr < i && x[ptr] <= x[i] - L) {
            if (dp[ptr] > -INF) {
                while (head < tail && dp[q[tail - 1]] <= dp[ptr]) {
                    tail--;
                }
                q[tail++] = ptr;
            }
            ptr++;
        }
        while (head < tail && x[q[head]] < x[i] - R) {
            head++;
        }
        if (head < tail) {
            dp[i] = dp[q[head]] + s[i];
            if (dp[i] >= k) return true;
        } else {
            dp[i] = -INF;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    bool first_case = true;
    while (cin >> n >> d >> k) {
        if (!first_case) cout << "\n";
        first_case = false;
        
        x.resize(n + 1);
        s.resize(n + 1);
        x[0] = 0;
        s[0] = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> x[i] >> s[i];
        }
        
        long long ans = -1;
        long long max_r = x[n];
        if (check(0)) {
            ans = 0;
        } else if (!check(max_r)) {
            ans = -1;
        } else {
            long long l = 0, r = max_r;
            while (l <= r) {
                long long mid = l + (r - l) / 2;
                if (check(mid)) {
                    ans = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
