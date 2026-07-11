#include <iostream>

using namespace std;

const int MAXN = 1000005;

int n, m;
int r[MAXN];
int d[MAXN];
int s[MAXN], t[MAXN];
long long diff[MAXN];

bool check(int mid) {
    for (int i = 1; i <= mid; ++i) {
        diff[s[i]] += d[i];
        diff[t[i] + 1] -= d[i];
    }
    long long cur = 0;
    bool ok = true;
    for (int i = 1; i <= n; ++i) {
        cur += diff[i];
        if (cur > r[i]) {
            ok = false;
            break;
        }
    }
    for (int i = 1; i <= mid; ++i) {
        diff[s[i]] -= d[i];
        diff[t[i] + 1] += d[i];
    }
    return ok;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            cin >> r[i];
        }
        for (int i = 1; i <= m; ++i) {
            cin >> d[i] >> s[i] >> t[i];
        }
        
        int low = 1, high = m, ans = m + 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (!check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        if (ans == m + 1) {
            cout << 0 << "\n";
        } else {
            cout << -1 << "\n" << ans << "\n";
        }
    }
    return 0;
}
