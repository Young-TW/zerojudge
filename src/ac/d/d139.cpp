#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int n = s.length();
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            int count = j - i;
            if (count >= 3) {
                cout << count << s[i];
            } else if (count == 2) {
                cout << s[i] << s[i];
            } else {
                cout << s[i];
            }
            i = j;
        }
        cout << "\n";
    }
    
    return 0;
}
