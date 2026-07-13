#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int ans = 0;
        int base = 1;
        for (int i = s.length() - 1; i >= 0; --i) {
            if (s[i] == '1') {
                ans += base;
            }
            base *= -2;
        }
        cout << ans << '\n';
    }
    
    return 0;
}
