#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        bool ok = true;
        bool seen[10] = {false};
        seen[0] = true;
        int curr = 0;
        
        for (char c : s) {
            int d = c - '0';
            if (d == 5) {
                ok = false;
                break;
            }
            curr = (curr + d) % 10;
            if (seen[(curr + 5) % 10]) {
                ok = false;
                break;
            }
            seen[curr] = true;
        }
        
        if (ok) {
            cout << "謝謝朋友們\n";
        } else {
            cout << "耗子尾汁，好好反思\n";
        }
    }
    
    return 0;
}
