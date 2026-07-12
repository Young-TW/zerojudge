#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        string ans;
        string temp;
        bool is_reverse = false;
        
        for (char c : s) {
            if (c == '+' || c == '-') {
                if (is_reverse) {
                    reverse(temp.begin(), temp.end());
                }
                ans += temp;
                temp.clear();
                is_reverse = (c == '-');
            } else {
                temp += c;
            }
        }
        
        if (is_reverse) {
            reverse(temp.begin(), temp.end());
        }
        ans += temp;
        
        cout << ans << "\n";
    }
    
    return 0;
}
