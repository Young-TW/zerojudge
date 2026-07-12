#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    char c;
    long long rem = 0;
    const int P = 131071;
    
    while (cin >> c) {
        if (c == '#') {
            if (rem == 0) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            rem = 0;
        } else if (c == '0' || c == '1') {
            rem = (rem * 2 + (c - '0')) % P;
        }
    }
    
    return 0;
}
