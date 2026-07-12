#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string row;
    while (cin >> row) {
        int sum = 0;
        for (char c : row) {
            sum += (c - '0');
        }
        cout << 45 - sum << "\n";
        
        for (int i = 0; i < 8; ++i) {
            cin >> row;
            sum = 0;
            for (char c : row) {
                sum += (c - '0');
            }
            cout << 45 - sum << "\n";
        }
    }
    
    return 0;
}
