#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<string> passwords(n);
        for (int i = 0; i < n; ++i) {
            cin >> passwords[i];
        }
        
        sort(passwords.begin(), passwords.end(), [](const string& a, const string& b) {
            if (a.length() != b.length()) {
                return a.length() < b.length();
            }
            return a < b;
        });
        
        size_t max_len = 0;
        for (const string& s : passwords) {
            if (s.length() > max_len) {
                max_len = s.length();
            }
        }
        
        for (const string& s : passwords) {
            cout << string(max_len - s.length(), ' ') << s << '\n';
        }
    }
    
    return 0;
}
