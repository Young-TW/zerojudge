#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    string s;
    while (cin >> n >> s) {
        for (char &c : s) {
            c ^= 32;
        }
        cout << s << '\n';
    }
    
    return 0;
}
