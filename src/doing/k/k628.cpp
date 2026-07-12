#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            string s;
            cin >> s;
            char c = s.back();
            string ruler;
            
            if (c == 'y' || c == 'Y') {
                ruler = "nobody";
            } else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                       c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                ruler = "Alice";
            } else {
                ruler = "Bob";
            }
            
            cout << "Case #" << i << ": " << s << " is ruled by " << ruler << ".\n";
        }
    }
    
    return 0;
}
