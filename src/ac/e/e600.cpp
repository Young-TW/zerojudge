#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        if (s.size() >= 3 && s[0] == 'U' && s[1] == '+') {
            unsigned int code = stoul(s.substr(2), nullptr, 16);
            
            unsigned char b1 = 0xE0 | ((code >> 12) & 0x0F);
            unsigned char b2 = 0x80 | ((code >> 6) & 0x3F);
            unsigned char b3 = 0x80 | (code & 0x3F);
            
            cout << bitset<8>(b1) << " " << bitset<8>(b2) << " " << bitset<8>(b3) << "\n";
            cout << (char)b1 << (char)b2 << (char)b3 << "\n";
        }
    }
    
    return 0;
}
