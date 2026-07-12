#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<pair<int, int>> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].first >> points[i].second;
        }
        
        sort(points.begin(), points.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second;
        });
        
        vector<int> lis;
        for (int i = 0; i < n; ++i) {
            int y = points[i].second;
            auto it = upper_bound(lis.begin(), lis.end(), y);
            if (it == lis.end()) {
                lis.push_back(y);
            } else {
                *it = y;
            }
        }
        
        cout << lis.size() << "\n";
    }
    
    return 0;
}
