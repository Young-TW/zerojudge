#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int s, a, b, c;
    while (cin >> s >> a >> b >> c) {
        if (s == 0 && a == 0 && b == 0 && c == 0) {
            break;
        }
        
        int degrees = 1080; // 2 full turns clockwise + 1 full turn counter-clockwise
        
        // 1. Turn clockwise from s to a
        degrees += ((s - a + 40) % 40) * 9;
        
        // 2. Turn counter-clockwise from a to b
        degrees += ((b - a + 40) % 40) * 9;
        
        // 3. Turn clockwise from b to c
        degrees += ((b - c + 40) % 40) * 9;
        
        cout << degrees << "\n";
    }
    
    return 0;
}
