#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    double r;
    while (cin >> r) {
        int val = (int)(r * 100.0 + 0.5);
        int ans = 0;
        if (val < 1500) ans = 20;
        else if (val < 1550) ans = 15;
        else if (val < 1600) ans = 10;
        else if (val < 1650) ans = 7;
        else if (val < 1700) ans = 3;
        else if (val < 1743) ans = 1;
        else ans = 0;
        cout << ans << '\n';
    }
    return 0;
}
