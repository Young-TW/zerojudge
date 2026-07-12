#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        if (s.empty()) {
            continue;
        }
        
        char max_char = s[0];
        int max_len = 1;
        char cur_char = s[0];
        int cur_len = 1;
        
        for (size_t i = 1; i < s.length(); ++i) {
            if (s[i] == cur_char) {
                cur_len++;
            } else {
                cur_char = s[i];
                cur_len = 1;
            }
            if (cur_len > max_len) {
                max_len = cur_len;
                max_char = cur_char;
            }
        }
        
        cout << max_char << " " << max_len << "\n";
    }
    
    return 0;
}
