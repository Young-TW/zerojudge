#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            vector<int> pos(n + 1);
            for (int i = 1; i <= n; ++i) {
                int x;
                cin >> x;
                pos[x] = i;
            }
            long long ans = 0;
            for (int a = 1; a <= n; ++a) {
                int mn = pos[a], mx = pos[a];
                for (int b = a + 1; b <= n; ++b) {
                    int p = pos[b];
                    if (p < mn) mn = p;
                    if (p > mx) mx = p;
                    if (mx - mn == b - a) {
                        if ((pos[a] == mn && pos[b] == mx) ||
                            (pos[a] == mx && pos[b] == mn)) {
                            ++ans;
                        }
                    }
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
