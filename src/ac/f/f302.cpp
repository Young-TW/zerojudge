#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        long long ans = 0;
        for (char c : s) {
            ans = ans * 9 + (c - '0');
        }
        cout << ans << '\n';
    }
    
    return 0;
}
