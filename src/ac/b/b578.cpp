#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        unsigned long long a, b, c;
        cin >> a >> b >> c;
        
        if (a > c) swap(a, c);
        if (b > c) swap(b, c);
        
        unsigned __int128 c2 = (unsigned __int128)c * c;
        unsigned __int128 ab = (unsigned __int128)a * a + (unsigned __int128)b * b;
        
        if (c2 < ab) {
            cout << "acute triangle\n";
        } else if (c2 == ab) {
            cout << "right triangle\n";
        } else {
            cout << "obtuse triangle\n";
        }
    }
    
    return 0;
}
