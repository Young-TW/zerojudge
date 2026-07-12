#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        string s;
        cin >> s;
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            char left_color = 'w';
            int left_count = 0;
            for (int j = 0; j < n; ++j) {
                char c = s[(i - j + n) % n];
                if (c == 'w') {
                    left_count++;
                } else if (left_color == 'w') {
                    left_color = c;
                    left_count++;
                } else if (c == left_color) {
                    left_count++;
                } else {
                    break;
                }
            }
            
            char right_color = 'w';
            int right_count = 0;
            for (int j = 0; j < n; ++j) {
                char c = s[(i + 1 + j) % n];
                if (c == 'w') {
                    right_count++;
                } else if (right_color == 'w') {
                    right_color = c;
                    right_count++;
                } else if (c == right_color) {
                    right_count++;
                } else {
                    break;
                }
            }
            
            ans = max(ans, min(left_count + right_count, n));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
