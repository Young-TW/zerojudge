#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int L;
    while (cin >> L && L) {
        string s;
        cin >> s;
        
        int min_dist = L;
        char last_char = '.';
        int last_pos = -1;
        
        for (int i = 0; i < L; ++i) {
            char c = s[i];
            if (c == 'Z') {
                min_dist = 0;
                break;
            } else if (c == 'R' || c == 'D') {
                if (last_char != '.' && last_char != c) {
                    min_dist = min(min_dist, i - last_pos);
                }
                last_char = c;
                last_pos = i;
            }
        }
        
        cout << min_dist << "\n";
    }
    
    return 0;
}
