#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int presses[256] = {0};
    presses[' '] = 1;
    string keys[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    for (int i = 0; i < 8; ++i) {
        for (size_t j = 0; j < keys[i].length(); ++j) {
            presses[(unsigned char)keys[i][j]] = j + 1;
        }
    }
    
    int T;
    if (!(cin >> T)) return 0;
    string s;
    getline(cin, s); // consume newline
    
    for (int t = 1; t <= T; ++t) {
        getline(cin, s);
        int ans = 0;
        for (size_t i = 0; i < s.length(); ++i) {
            ans += presses[(unsigned char)s[i]];
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
    
    return 0;
}
