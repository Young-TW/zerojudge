#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (getline(cin, s)) {
        bool is_teacher = false;
        for (char c : s) {
            if (c == '!') {
                is_teacher = true;
                break;
            }
        }
        
        if (is_teacher) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
