#include <iostream>
#include <vector>
#include <utility>
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
        sort(points.begin(), points.end());
        for (int i = 0; i < n; ++i) {
            cout << points[i].first << " " << points[i].second << "\n";
        }
    }
    
    return 0;
}
