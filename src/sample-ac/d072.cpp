#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            int y;
            cin >> y;
            bool leap = (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
            cout << "Case " << i << ": " << (leap ? "a leap year" : "a normal year") << "\n";
        }
    }
    
    return 0;
}
