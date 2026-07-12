#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    while (cin >> t) {
        while (t--) {
            int y;
            if (cin >> y) {
                if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)) {
                    cout << "a leap year\n";
                } else {
                    cout << "a normal year\n";
                }
            } else {
                break;
            }
        }
    }
    
    return 0;
}
