#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int diff[1000005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    int case_num = 1;
    while (cin >> s) {
        int n;
        cin >> n;
        
        diff[0] = 0;
        for (size_t i = 1; i < s.length(); ++i) {
            diff[i] = diff[i-1] + (s[i] != s[i-1] ? 1 : 0);
        }
        
        cout << "Case " << case_num++ << ":\n";
        for (int k = 0; k < n; ++k) {
            int i, j;
            cin >> i >> j;
            int l = min(i, j);
            int r = max(i, j);
            
            if (diff[r] - diff[l] == 0) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    return 0;
}
