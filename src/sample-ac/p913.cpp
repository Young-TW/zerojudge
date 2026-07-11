#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    while (cin >> a >> b) {
        if (a <= 1) {
            if (a == 1 && b >= 1) {
                cout << 1 << "\n";
            } else if (a == 0 && b >= 0) {
                cout << 0 << "\n";
            }
            continue;
        }
        
        long long cur = a;
        while (cur <= b) {
            cout << cur << "\n";
            if (cur > b / a) {
                break;
            }
            cur *= a;
        }
    }
    
    return 0;
}
