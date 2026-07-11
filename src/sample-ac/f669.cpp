#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        reverse(s.begin(), s.end());
        cout << s << "\n";
    }
    
    return 0;
}
