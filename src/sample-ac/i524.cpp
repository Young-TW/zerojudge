#include <iostream>
#include <string>
#include <list>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        list<char> text;
        list<char>::iterator it = text.begin();
        
        for (char c : s) {
            if (c == '[') {
                it = text.begin();
            } else if (c == ']') {
                it = text.end();
            } else {
                text.insert(it, c);
            }
        }
        
        string out(text.begin(), text.end());
        cout << out << '\n';
    }
    
    return 0;
}
