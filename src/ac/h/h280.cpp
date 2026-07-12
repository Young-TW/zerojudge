#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s1, s2;
    while (getline(cin, s1) && getline(cin, s2)) {
        cout << s1 << s2 << "\n";
    }
    
    return 0;
}
