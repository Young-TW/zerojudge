#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        unsigned int g = 0;
        for (char c : s) {
            g = (g << 1) | (c - '0');
        }
        
        unsigned int n = g;
        n ^= n >> 1;
        n ^= n >> 2;
        n ^= n >> 4;
        n ^= n >> 8;
        n ^= n >> 16;
        
        cout << n << '\n';
    }
    
    return 0;
}
