#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        if (s[0] == '-') break;
        if (s.size() >= 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
            unsigned int val;
            sscanf(s.c_str(), "%x", &val);
            cout << val << "\n";
        } else {
            unsigned int val;
            sscanf(s.c_str(), "%u", &val);
            cout << "0x" << uppercase << hex << val << dec << "\n";
        }
    }
    return 0;
}
