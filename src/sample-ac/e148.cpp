#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    string s;
    while (T-- && cin >> s) {
        int n = (int)s.length();
        if (n == 0) {
            cout << 1 << "\n";
            continue;
        }
        
        int i = 0, j = 1, k = 0;
        while (j + k < n) {
            char a = s[i + k];
            char b = s[j + k];
            if (a == b) {
                k++;
            } else if (a < b) {
                j = j + k + 1;
                if (i == j) j++;
                k = 0;
            } else {
                i = max(i + k + 1, j);
                j = i + 1;
                k = 0;
            }
        }
        
        cout << i + 1 << "\n";
    }
    
    return 0;
}
