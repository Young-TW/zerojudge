#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n) {
        vector<pair<int, int>> pts(n);
        int min_x = INT_MAX, max_x = INT_MIN;
        int min_y = INT_MAX, max_y = INT_MIN;
        
        for (int i = 0; i < n; ++i) {
            cin >> pts[i].first >> pts[i].second;
            if (pts[i].first < min_x) min_x = pts[i].first;
            if (pts[i].first > max_x) max_x = pts[i].first;
            if (pts[i].second < min_y) min_y = pts[i].second;
            if (pts[i].second > max_y) max_y = pts[i].second;
        }
        
        int sum_x = min_x + max_x;
        int sum_y = min_y + max_y;
        
        sort(pts.begin(), pts.end());
        
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            pair<int, int> target = {sum_x - pts[i].first, sum_y - pts[i].second};
            if (!binary_search(pts.begin(), pts.end(), target)) {
                ok = false;
                break;
            }
        }
        
        if (ok) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
    
    return 0;
}
