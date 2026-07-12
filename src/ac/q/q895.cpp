#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            int n = s.length();
            string best = s;
            for (int i = 1; i < n; ++i) {
                string cur = s.substr(i) + s.substr(0, i);
                if (cur < best) {
                    best = cur;
                }
            }
            cout << best << '\n';
        }
    }
    
    return 0;
}
