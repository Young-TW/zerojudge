#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int v, a, b;
    while (cin >> v >> a >> b) {
        unsigned int uv = static_cast<unsigned int>(v);
        unsigned int mask = 1u << a;
        
        if (b == 1) {
            uv |= mask;
        } else {
            uv &= ~mask;
        }
        
        for (int i = 31; i >= 0; --i) {
            cout << ((uv >> i) & 1);
        }
        cout << '\n';
    }
    
    return 0;
}
