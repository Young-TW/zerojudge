#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int T;
    if (!(cin >> T)) return 0;
    for (int t = 1; t <= T; ++t) {
        vector<pair<string,int>> v(10);
        int mx = 0;
        for (int i = 0; i < 10; ++i) {
            cin >> v[i].first >> v[i].second;
            mx = max(mx, v[i].second);
        }
        cout << "Case #" << t << ":\n";
        for (auto &p : v) {
            if (p.second == mx) cout << p.first << "\n";
        }
    }
    return 0;
}
