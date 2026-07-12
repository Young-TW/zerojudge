#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (getline(cin, s)) {
        cout << s << '\n';
        cout << string(s.length(), '~') << '\n';
    }
    
    return 0;
}
