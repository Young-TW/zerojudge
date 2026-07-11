#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    while (cin >> s) {
        int n = s.length();
        string ans = s;
        int i = 0;
        while (i < n) {
            if (s[i] == 'X') {
                int l = i;
                while (i < n && s[i] == 'X') {
                    i++;
                }
                int r = i - 1;
                char left_char = (l > 0) ? s[l - 1] : ' ';
                char right_char = (r < n - 1) ? s[r + 1] : ' ';
                if (left_char == 'R' && right_char == 'L') {
                    int len = r - l + 1;
                    int half = len / 2;
                    for (int j = l; j < l + half; ++j) ans[j] = 'R';
                    for (int j = r - half + 1; j <= r; ++j) ans[j] = 'L';
                } else if (left_char == 'R') {
                    for (int j = l; j <= r; ++j) ans[j] = 'R';
                } else if (right_char == 'L') {
                    for (int j = l; j <= r; ++j) ans[j] = 'L';
                }
            } else {
                i++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
