#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        while (!s.empty()) {
            cout << s << "\n";
            s.pop_back();
        }
    }
    
    return 0;
}
