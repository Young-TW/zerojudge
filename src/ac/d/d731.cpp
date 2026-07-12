#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int p;
    while (cin >> p) {
        while (p--) {
            int n;
            cin >> n;
            vector<int> v(n);
            for (int i = 0; i < n; ++i) {
                cin >> v[i];
            }
            sort(v.begin(), v.end(), [](int a, int b) {
                int abs_a = a < 0 ? -a : a;
                int abs_b = b < 0 ? -b : b;
                return abs_a < abs_b;
            });
            int ans = 0;
            int last = 0;
            for (int x : v) {
                int cur = (x > 0) ? 1 : -1;
                if (ans == 0 || cur != last) {
                    ans++;
                    last = cur;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
