#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int n;
        cin >> n;
        string current(s.length(), '*');
        cout << current << "\n";
        for (int i = 0; i < n; ++i) {
            char c;
            cin >> c;
            for (size_t j = 0; j < s.length(); ++j) {
                if (s[j] == c) {
                    current[j] = c;
                }
            }
            cout << current << "\n";
        }
    }
    
    return 0;
}
