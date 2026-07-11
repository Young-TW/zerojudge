#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long T;
    while (cin >> T) {
        while (T--) {
            long long H, R, hours;
            cin >> H >> R >> hours;
            cout << H + R * hours << '\n';
        }
    }
    
    return 0;
}
