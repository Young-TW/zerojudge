#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        for (char c : s) {
            if (c == 'T') cout << 'A';
            else if (c == 'A') cout << 'U';
            else if (c == 'G') cout << 'C';
            else if (c == 'C') cout << 'G';
        }
        cout << '\n';
    }
    
    return 0;
}
