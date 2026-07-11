#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int sum = 0;
        for (char c : s) {
            if (c >= '0' && c <= '9') {
                sum += c - '0';
            }
        }
        if (sum % 3 == 0) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
    
    return 0;
}
