#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int mod = 0;
        for (char c : s) {
            mod = (mod * 10 + (c - '0')) % 17;
        }
        
        if (mod == 0) {
            cout << "Yes\n";
        } else {
            cout << mod << "\n";
        }
    }
    
    return 0;
}
