#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    while (cin >> m) {
        while (m--) {
            int n;
            cin >> n;
            vector<long long> a(n), x(n), p(n);
            long long W = 0;
            for (int i = 0; i < n; i++) {
                cin >> a[i] >> x[i];
                p[i] = x[i] / a[i];
                W += a[i];
            }
            vector<int> idx(n);
            iota(idx.begin(), idx.end(), 0);
            sort(idx.begin(), idx.end(), [&](int u, int v) {
                return p[u] < p[v];
            });
            long long half = (W + 1) / 2;
            long long acc = 0, bestX = p[idx[0]];
            for (int j = 0; j < n; j++) {
                acc += a[idx[j]];
                if (acc >= half) {
                    bestX = p[idx[j]];
                    break;
                }
            }
            long long sum = 0;
            for (int i = 0; i < n; i++) {
                sum += llabs(a[i] * bestX - x[i]);
            }
            cout << sum << "\n";
        }
    }
    return 0;
}
