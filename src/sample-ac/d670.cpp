#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    string table = "22233344455566677778889999";
    
    while (cin >> s) {
        for (char c : s) {
            if (c == '-' || c == '0' || c == '1') {
                cout << c;
            } else if (c >= 'A' && c <= 'Z') {
                cout << table[c - 'A'];
            }
        }
        cout << "\n";
    }
    
    return 0;
}
