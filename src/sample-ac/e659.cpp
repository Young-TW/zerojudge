#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    int ans = 0;
    
    while (cin >> s) {
        int op_pos = s.find('+');
        if (op_pos == string::npos) {
            op_pos = s.find('-');
        }
        
        int eq_pos = s.find('=');
        
        int a = stoi(s.substr(0, op_pos));
        char op = s[op_pos];
        int b = stoi(s.substr(op_pos + 1, eq_pos - op_pos - 1));
        string c_str = s.substr(eq_pos + 1);
        
        if (c_str != "?") {
            int c = stoi(c_str);
            if (op == '+') {
                if (a + b == c) {
                    ans++;
                }
            } else {
                if (a - b == c) {
                    ans++;
                }
            }
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
