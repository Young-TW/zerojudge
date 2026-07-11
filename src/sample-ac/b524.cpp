#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        long long ans = 0;
        int cnt_y = 0;
        int cnt_e = 0;
        
        for (char c : s) {
            if (c == 'y') {
                int less_e = 2 * cnt_y;
                if (less_e > cnt_e) {
                    ans += (less_e - cnt_e);
                }
                cnt_y++;
            } else if (c == 'e') {
                int E = 3 * (cnt_e / 2) + 1 + (cnt_e % 2);
                int less_y = (E + 2) / 3;
                if (less_y > cnt_y) {
                    ans += (less_y - cnt_y);
                }
                cnt_e++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
