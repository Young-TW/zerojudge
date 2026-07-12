#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int weights[5] = {16, 8, 4, 2, 1};
    string line;
    
    while (getline(cin, line)) {
        int ans = 0;
        int idx = 0;
        for (char c : line) {
            if (c == '1' || c == '0') {
                if (c == '1') {
                    ans += weights[idx];
                }
                idx++;
                if (idx == 5) {
                    break;
                }
            }
        }
        if (idx > 0) {
            cout << ans << "\n";
        }
    }
    
    return 0;
}
