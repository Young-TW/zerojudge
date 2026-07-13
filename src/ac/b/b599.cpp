#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n) {
        vector<int> d(n);
        long long sum = 0;
        bool valid = true;
        for (int i = 0; i < n; ++i) {
            cin >> d[i];
            sum += d[i];
            if (d[i] < 0 || d[i] >= n) {
                valid = false;
            }
        }
        if (!valid || sum % 2 != 0) {
            cout << "N\n";
            continue;
        }

        sort(d.begin(), d.end(), greater<int>());
        
        bool ok = true;
        long long prefix_sum = 0;
        for (int k = 1; k <= n; ++k) {
            prefix_sum += d[k - 1];
            long long right_sum = 0;
            for (int i = k; i < n; ++i) {
                right_sum += min(d[i], k);
            }
            if (prefix_sum > (long long)k * (k - 1) + right_sum) {
                ok = false;
                break;
            }
        }
        if (ok) cout << "Y\n";
        else cout << "N\n";
    }
    return 0;
}
