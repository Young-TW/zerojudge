#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        while (n--) {
            long long h, m, s;
            cin >> h >> m >> s;
            long long total_alien_seconds = h * 32 * 16 + m * 16 + s;
            long long total_earth_seconds = total_alien_seconds * 4;
            
            long long earth_h = total_earth_seconds / 3600;
            long long earth_m = (total_earth_seconds % 3600) / 60;
            long long earth_s = total_earth_seconds % 60;
            
            cout << earth_h << ":" << earth_m << ":" << earth_s << "\n";
        }
    }
    
    return 0;
}
