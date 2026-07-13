#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int n = s.length();
        int max_dist = 0;
        int i = 0;
        
        while (i < n) {
            if (s[i] == '.') {
                int j = i;
                while (j < n && s[j] == '.') {
                    j++;
                }
                int len = j - i;
                if (i == 0 || j == n) {
                    max_dist = max(max_dist, len - 1);
                } else {
                    max_dist = max(max_dist, (len - 1) / 2);
                }
                i = j;
            } else {
                i++;
            }
        }
        
        cout << max_dist << "\n";
    }
    
    return 0;
}
