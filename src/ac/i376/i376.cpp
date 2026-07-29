#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<vector<long long>> a(n, vector<long long>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> a[i][j];

        vector<long long> rowMax(n), colMin(n);

        for (int i = 0; i < n; ++i) {
            long long mx = a[i][0];
            for (int j = 1; j < n; ++j)
                mx = max(mx, a[i][j]);
            rowMax[i] = mx;
        }

        for (int j = 0; j < n; ++j) {
            long long mn = a[0][j];
            for (int i = 1; i < n; ++i)
                mn = min(mn, a[i][j]);
            colMin[j] = mn;
        }

        bool found = false;
        for (int i = 0; i < n && !found; ++i) {
            for (int j = 0; j < n && !found; ++j) {
                if (a[i][j] == rowMax[i] && a[i][j] == colMin[j]) {
                    cout << i << " " << j << "\n";
                    found = true;
                }
            }
        }

        if (!found)
            cout << "NO\n";
    }

    return 0;
}
