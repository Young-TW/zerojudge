#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    while (cin >> t) {
        while (t--) {
            string s;
            cin >> s;
            int rem = 0;
            for (size_t i = 0; i < s.length(); ++i) {
                rem = (rem * 2 + (s[i] - '0')) % 3;
            }
            if (rem == 0) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    
    return 0;
}
