#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (getline(cin, s)) {
        size_t first = s.find('|');
        size_t last = s.rfind('|');
        
        if (first != string::npos && last != string::npos && first < last) {
            int val = 0;
            int bit = 0;
            for (int i = last - 1; i > (int)first; --i) {
                if (s[i] == 'o') {
                    val += (1 << bit);
                    bit++;
                } else if (s[i] == ' ') {
                    bit++;
                }
            }
            cout << (char)val;
        }
    }
    
    return 0;
}
