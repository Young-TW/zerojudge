#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        string cur;
        int cnt = 0;
        bool has_digit = false;
        bool has_content = false;
        
        for (char c : line) {
            if (c >= '0' && c <= '9') {
                cnt += c - '0';
                has_digit = true;
                has_content = true;
            } else if (c == '!') {
                cout << cur << '\n';
                cur.clear();
                cnt = 0;
                has_digit = false;
                has_content = true;
            } else if (c == 'b' || (c >= 'A' && c <= 'Z') || c == '*') {
                if (!has_digit) {
                    cnt = 1;
                }
                cur.append(cnt, (c == 'b' ? ' ' : c));
                cnt = 0;
                has_digit = false;
                has_content = true;
            }
        }
        
        if (!cur.empty() || !has_content) {
            cout << cur << '\n';
        }
    }
    
    return 0;
}
