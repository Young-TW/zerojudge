#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        string s, t;
        cin >> s >> t;
        
        vector<int> fail(m, 0);
        for (int i = 1; i < m; ++i) {
            int j = fail[i - 1];
            while (j > 0 && t[i] != t[j]) {
                j = fail[j - 1];
            }
            if (t[i] == t[j]) {
                j++;
            }
            fail[i] = j;
        }
        
        int j = 0;
        int pos = -1;
        for (int i = 0; i < n; ++i) {
            while (j > 0 && s[i] != t[j]) {
                j = fail[j - 1];
            }
            if (s[i] == t[j]) {
                j++;
            }
            if (j == m) {
                pos = i - m + 1;
                break;
            }
        }
        
        if (pos != -1) {
            cout << "Yes\n";
            cout << "pos: " << pos << "\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
