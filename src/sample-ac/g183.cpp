#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string n;
    while (cin >> n) {
        int rem = 0;
        for (size_t i = 0; i < n.size(); ++i) {
            rem = (rem * 10 + (n[i] - '0')) % 81;
        }
        if (rem == 0) {
            cout << "konopad!\n";
        } else {
            cout << "konosuba!\n";
        }
    }
    
    return 0;
}
