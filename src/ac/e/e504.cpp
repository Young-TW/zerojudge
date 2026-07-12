#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s && s != "*") {
        int ans = 0;
        int current_sum = 0;
        for (char c : s) {
            if (c == '/') {
                if (current_sum == 64) {
                    ans++;
                }
                current_sum = 0;
            } else {
                switch (c) {
                    case 'W': current_sum += 64; break;
                    case 'H': current_sum += 32; break;
                    case 'Q': current_sum += 16; break;
                    case 'E': current_sum += 8; break;
                    case 'S': current_sum += 4; break;
                    case 'T': current_sum += 2; break;
                    case 'X': current_sum += 1; break;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
