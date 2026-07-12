#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long h, x, y;
    while (cin >> h >> x >> y) {
        if (h <= x) {
            cout << 1 << "\n";
        } else {
            long long diff = x - y;
            long long rem = h - x;
            long long t = (rem + diff - 1) / diff + 1;
            cout << t << "\n";
        }
    }
    
    return 0;
}
