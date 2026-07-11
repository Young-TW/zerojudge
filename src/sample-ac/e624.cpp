#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s, t;
    while (cin >> s >> t) {
        size_t idx = 0;
        for (char c : t) {
            if (idx < s.length() && c == s[idx]) {
                idx++;
            }
        }
        if (idx == s.length()) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
