#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int countBits(int n) {
    int cnt = 0;
    while (n) {
        cnt += n & 1;
        n >>= 1;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            string s;
            cin >> s;
            
            int b1 = countBits(stoi(s));
            
            int b2 = 0;
            for (char c : s) {
                int hex_val;
                if (c >= '0' && c <= '9') {
                    hex_val = c - '0';
                } else {
                    hex_val = tolower(c) - 'a' + 10;
                }
                b2 += countBits(hex_val);
            }
            
            cout << b1 << " " << b2 << "\n";
        }
    }
    return 0;
}
