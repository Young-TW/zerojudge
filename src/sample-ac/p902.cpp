#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (getline(cin, s)) {
        int n;
        if (!(cin >> n)) break;
        cin.ignore();
        
        n = (n % 26 + 26) % 26;
        for (char &c : s) {
            if (c >= 'A' && c <= 'Z') {
                c = 'A' + (c - 'A' + n) % 26;
            } else if (c >= 'a' && c <= 'z') {
                c = 'a' + (c - 'a' + n) % 26;
            }
        }
        cout << s << "\n";
    }
    
    return 0;
}
