#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    char type;
    while (cin >> type) {
        if (type == 'A') {
            long long h, x, y;
            cin >> h >> x >> y;
            cout << h - y << "\n";
        } else if (type == 'B') {
            long long t, x, y;
            cin >> t >> x >> y;
            cout << t + y << "\n";
        }
    }
    
    return 0;
}
