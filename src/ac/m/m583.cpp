#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        vector<int> mark(n + 1, 0);
        int ans = 0;

        for (int i = 1; i <= n; ++i) {
            if (mark[i]) continue;
            int cur = i;
            while (!mark[cur]) {
                mark[cur] = i;
                cur = a[cur];
            }
            if (mark[cur] == i) {
                int len = 0;
                int x = cur;
                do {
                    ++len;
                    x = a[x];
                } while (x != cur);
                ans = max(ans, len);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
