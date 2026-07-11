#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        string s;
        cin >> s;
        int r = 0, g = 0, b = 0;
        for (char c : s) {
            if (c == 'r') {
                r++;
            } else if (c == 'g') {
                g = max(r, g) + 1;
            } else if (c == 'b') {
                b = max(g, b) + 1;
            }
        }
        cout << max(r, max(g, b)) << "\n";
    }
    return 0;
}
