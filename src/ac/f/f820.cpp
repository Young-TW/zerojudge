#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        int t;
        cin >> t;
        --t;
        int dir;
        if (t == 0) dir = 1;
        else if (t == n - 1) dir = -1;
        else dir = (a[t + 1] < a[t - 1]) ? 1 : -1;
        for (;;) {
            int nt = t + dir;
            if (nt < 0 || nt >= n) break;
            if (a[nt] <= a[t]) t = nt;
            else break;
        }
        cout << t + 1 << '\n';
    }
    return 0;
}
