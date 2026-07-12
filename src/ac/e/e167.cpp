#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        
        vector<pair<int, int>> points;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int val;
                cin >> val;
                if (val == 1) {
                    points.emplace_back(i, j);
                }
            }
        }
        
        int start_x, start_y;
        cin >> start_x >> start_y;
        pair<int, int> current = {start_x, start_y};
        
        vector<pair<int, int>> unvisited;
        unvisited.reserve(points.size() - 1);
        for (const auto& p : points) {
            if (p != current) {
                unvisited.push_back(p);
            }
        }
        
        while (!unvisited.empty()) {
            long long best_dist = -1;
            int best_idx = -1;
            pair<int, int> best_point;
            
            for (int i = 0; i < (int)unvisited.size(); ++i) {
                long long dx = current.first - unvisited[i].first;
                long long dy = current.second - unvisited[i].second;
                long long dist = dx * dx + dy * dy;
                
                if (best_idx == -1 || dist < best_dist ||
                    (dist == best_dist && 
                     (unvisited[i].first < best_point.first || 
                      (unvisited[i].first == best_point.first && unvisited[i].second < best_point.second)))) {
                    best_dist = dist;
                    best_point = unvisited[i];
                    best_idx = i;
                }
            }
            
            current = best_point;
            unvisited[best_idx] = unvisited.back();
            unvisited.pop_back();
        }
        
        cout << current.first << ' ' << current.second << '\n';
    }
    
    return 0;
}
