#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int ans = 0;
        for (char c : s) {
            if (c == '0' || c == '6' || c == '9') {
                ans += 1;
            } else if (c == '8') {
                ans += 2;
            }
        }
        cout << ans << '\n';
    }
    
    return 0;
}
