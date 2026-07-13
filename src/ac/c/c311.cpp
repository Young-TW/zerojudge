#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string n;
    while (cin >> n) {
        int ans = 0;
        for (char c : n) {
            ans = (ans * 10 + (c - '0')) % 91;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
