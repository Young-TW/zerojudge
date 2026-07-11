#include <iostream>
#include <string>

using namespace std;

long long len[55];

void solve(int n, long long L, long long R, string& ans) {
    if (n == 0) {
        for (long long i = L; i <= R; i++) ans += '0';
        return;
    }
    if (n == 1) {
        for (long long i = L; i <= R; i++) ans += '1';
        return;
    }
    if (R < len[n-2]) {
        solve(n - 2, L, R, ans);
    } else if (L >= len[n-2]) {
        solve(n - 1, L - len[n-2], R - len[n-2], ans);
    } else {
        solve(n - 2, L, len[n-2] - 1, ans);
        solve(n - 1, 0, R - len[n-2], ans);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    len[0] = 1;
    len[1] = 1;
    for (int i = 2; i <= 54; i++) {
        len[i] = len[i-1] + len[i-2];
    }

    int T;
    while (cin >> T) {
        while (T--) {
            long long N, L, R;
            cin >> N >> L >> R;
            if (N >= 50) {
                if (N % 2 == 0) N = 48;
                else N = 49;
            }
            string ans;
            ans.reserve(static_cast<size_t>(R - L + 1));
            solve(static_cast<int>(N), L, R, ans);
            cout << ans << "\n";
        }
    }
    return 0;
}
