#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<pair<int,int>> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].first >> p[i].second;
        }

        long long bestDist = LLONG_MAX;
        int bestX = 0, bestY = 0;

        for (int i = 0; i < n; ++i) {
            long long cur = 0;
            for (int j = 0; j < n; ++j) {
                cur += llabs(p[j].first  - p[i].first);
                cur += llabs(p[j].second - p[i].second);
            }
            if (cur < bestDist ||
               (cur == bestDist && (p[i].first < bestX ||
                                   (p[i].first == bestX && p[i].second < bestY)))) {
                bestDist = cur;
                bestX = p[i].first;
                bestY = p[i].second;
            }
        }

        cout << bestX << ' ' << bestY << '\n';
        cout << bestDist << '\n';
    }
    return 0;
}
