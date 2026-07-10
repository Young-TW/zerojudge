#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<int> xs(n), ys(n);
        for (int i = 0; i < n; i++) cin >> xs[i] >> ys[i];

        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());

        int loX = xs[(n - 1) / 2], hiX = xs[n / 2];
        int loY = ys[(n - 1) / 2], hiY = ys[n / 2];

        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += llabs(xs[i] - loX);
            sum += llabs(ys[i] - loY);
        }

        long long cnt = (long long)(hiX - loX + 1) * (long long)(hiY - loY + 1);

        cout << sum << ' ' << cnt << '\n';
    }
    return 0;
}
