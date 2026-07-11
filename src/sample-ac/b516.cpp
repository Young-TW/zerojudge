#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (cin >> n) {
        while (n--) {
            string s;
            if (cin >> s) {
                for (char &c : s) {
                    if (c >= 'A' && c <= 'Z') {
                        c = (c - 'A' + 3) % 26 + 'A';
                    } else if (c >= 'a' && c <= 'z') {
                        c = (c - 'a' + 3) % 26 + 'a';
                    }
                }
                cout << s << "\n";
            }
        }
    }
    
    return 0;
}
