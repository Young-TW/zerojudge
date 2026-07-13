#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, n;
    while (cin >> m >> n) {
        vector<int> e(m);
        for (int i = 0; i < m; ++i) {
            cin >> e[i];
        }
        
        long long total_distance = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            auto it = lower_bound(e.begin(), e.end(), x);
            long long pos;
            if (it == e.end()) {
                pos = m + 1;
            } else {
                pos = distance(e.begin(), it) + 1;
            }
            total_distance += pos * 2;
        }
        cout << total_distance << "\n";
    }
    
    return 0;
}
