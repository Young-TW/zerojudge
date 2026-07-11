#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    
    string dummy;
    getline(cin, dummy);
    
    while (T--) {
        string line;
        getline(cin, line);
        
        long long ans = 0;
        long long num = 0;
        char op = '+';
        size_t i = 0;
        size_t n = line.length();
        bool firstNum = true;
        
        while (i < n) {
            while (i < n && line[i] == ' ') i++;
            if (i == n) break;
            
            if (line[i] >= '0' && line[i] <= '9') {
                num = 0;
                while (i < n && line[i] >= '0' && line[i] <= '9') {
                    num = num * 10 + (line[i] - '0');
                    i++;
                }
                if (firstNum) {
                    ans = num;
                    firstNum = false;
                } else {
                    if (op == '+') ans += num;
                    else if (op == '-') ans -= num;
                    else if (op == '*') ans *= num;
                    else if (op == '/') ans /= num;
                }
            } else {
                op = line[i];
                i++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
