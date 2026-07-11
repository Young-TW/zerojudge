#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n) {
        long long x, y, z, L;
        cin >> x >> y >> z >> L;
        
        long long max_x = x, min_x = x + L;
        long long max_y = y, min_y = y + L;
        long long max_z = z, min_z = z + L;
        
        for (int i = 1; i < n; ++i) {
            cin >> x >> y >> z >> L;
            max_x = max(max_x, x);
            min_x = min(min_x, x + L);
            max_y = max(max_y, y);
            min_y = min(min_y, y + L);
            max_z = max(max_z, z);
            min_z = min(min_z, z + L);
        }
        
        long long dx = max(0LL, min_x - max_x);
        long long dy = max(0LL, min_y - max_y);
        long long dz = max(0LL, min_z - max_z);
        
        cout << dx * dy * dz << "\n";
    }
    
    return 0;
}
