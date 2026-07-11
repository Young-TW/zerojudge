#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        if (s[0] == '#') {
            int r, g, b;
            sscanf(s.c_str(), "#%2x%2x%2x", &r, &g, &b);
            cout << r << " " << g << " " << b << "\n";
        } else {
            int r = stoi(s);
            int g, b;
            cin >> g >> b;
            printf("#%02X%02X%02X\n", r, g, b);
        }
    }
    
    return 0;
}
