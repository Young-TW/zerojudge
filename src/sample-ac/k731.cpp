#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<pair<int, int>> pts(n + 1);
        pts[0] = {0, 0};
        for (int i = 1; i <= n; ++i) {
            cin >> pts[i].first >> pts[i].second;
        }
        
        int left = 0, right = 0, uturn = 0;
        
        for (int i = 1; i < n; ++i) {
            int vx1 = pts[i].first - pts[i-1].first;
            int vy1 = pts[i].second - pts[i-1].second;
            int vx2 = pts[i+1].first - pts[i].first;
            int vy2 = pts[i+1].second - pts[i].second;
            
            int cross = vx1 * vy2 - vy1 * vx2;
            if (cross > 0) {
                left++;
            } else if (cross < 0) {
                right++;
            } else {
                int dot = vx1 * vx2 + vy1 * vy2;
                if (dot < 0) {
                    uturn++;
                }
            }
        }
        
        cout << left << " " << right << " " << uturn << "\n";
    }
    
    return 0;
}
