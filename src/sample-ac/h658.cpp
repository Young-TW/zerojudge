#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long X, Y;
    while (cin >> X >> Y) {
        int N;
        if (!(cin >> N)) break;
        
        long long best_x = 0, best_y = 0;
        long long min_dist = -1;
        
        for (int i = 0; i < N; ++i) {
            long long x, y;
            cin >> x >> y;
            
            long long dx = x - X;
            if (dx < 0) dx = -dx;
            long long dy = y - Y;
            if (dy < 0) dy = -dy;
            long long dist = dx + dy;
            
            if (min_dist == -1 || dist < min_dist) {
                min_dist = dist;
                best_x = x;
                best_y = y;
            }
        }
        
        cout << best_x << " " << best_y << "\n";
    }
    
    return 0;
}
