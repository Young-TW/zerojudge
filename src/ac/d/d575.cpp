#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int cx, cy, px, py, r;
    while (cin >> cx >> cy >> px >> py >> r) {
        long long dx = static_cast<long long>(px) - cx;
        if (dx < 0) dx = -dx;
        long long dy = static_cast<long long>(py) - cy;
        if (dy < 0) dy = -dy;
        
        if (dx + dy <= r) {
            cout << "die\n";
        } else {
            cout << "alive\n";
        }
    }
    
    return 0;
}
