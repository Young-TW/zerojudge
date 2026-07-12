#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    bool first_line = true;
    while (getline(cin, line)) {
        if (!first_line) {
            cout << "\n";
        }
        first_line = false;
        
        bool first_word = true;
        bool in_word = false;
        for (char c : line) {
            if (c == ' ') {
                in_word = false;
            } else {
                if (!in_word) {
                    if (!first_word) {
                        cout << ' ';
                    }
                    first_word = false;
                    in_word = true;
                }
                cout << c;
            }
        }
    }
    
    return 0;
}
