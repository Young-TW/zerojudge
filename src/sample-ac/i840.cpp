#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s[5];
    while (cin >> s[0] >> s[1] >> s[2] >> s[3] >> s[4]) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                cout << s[j][i];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
