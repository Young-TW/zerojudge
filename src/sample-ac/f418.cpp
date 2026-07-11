#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int h, w, r1, c1, r2, c2;
    while (cin >> h >> w >> r1 >> c1 >> r2 >> c2) {
        vector<string> grid(h);
        for (int i = 0; i < h; ++i) {
            cin >> grid[i];
        }
        
        string ans;
        int dr = (r2 == r1) ? 0 : 1;
        int dc = (c2 == c1) ? 0 : 1;
        
        int curr_r = r1 - 1;
        int curr_c = c1 - 1;
        
        while (true) {
            ans += grid[curr_r][curr_c];
            if (curr_r == r2 - 1 && curr_c == c2 - 1) {
                break;
            }
            curr_r += dr;
            curr_c += dc;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
