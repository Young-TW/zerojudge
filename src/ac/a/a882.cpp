#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            int ans = 0;
            for (char c : s) {
                if (c == 'X') {
                    ans += 2;
                } else if (c == 'H') {
                    ans += 1;
                }
            }
            cout << ans << '\n';
        }
    }
    
    return 0;
}
