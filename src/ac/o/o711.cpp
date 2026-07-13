#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        long long w1, w2, h1, h2;
        cin >> w1 >> w2 >> h1 >> h2;
        
        long long area1 = w1 * w1;
        long long area2 = w2 * w2;
        long long vol1 = area1 * h1;
        long long vol2 = area2 * h2;
        long long total_v = vol1 + vol2;
        
        long long curr_v = 0;
        long long curr_h = 0;
        long long max_delta = 0;
        
        for (int i = 0; i < n; ++i) {
            long long v;
            cin >> v;
            
            long long new_v = min(curr_v + v, total_v);
            long long new_h;
            if (new_v <= vol1) {
                new_h = new_v / area1;
            } else {
                new_h = h1 + (new_v - vol1) / area2;
            }
            
            long long delta = new_h - curr_h;
            if (delta > max_delta) {
                max_delta = delta;
            }
            
            curr_v = new_v;
            curr_h = new_h;
        }
        
        cout << max_delta << "\n";
    }
    
    return 0;
}
