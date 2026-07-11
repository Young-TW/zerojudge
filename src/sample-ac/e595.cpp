#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        int n = s.length();
        if (n == 0) {
            cout << "\n";
            continue;
        }
        
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        
        string p = rev_s + "#" + s;
        int m = p.length();
        
        vector<int> pi(m, 0);
        for (int i = 1; i < m; ++i) {
            int j = pi[i - 1];
            while (j > 0 && p[i] != p[j]) {
                j = pi[j - 1];
            }
            if (p[i] == p[j]) {
                j++;
            }
            pi[i] = j;
        }
        
        int k = pi[m - 1];
        string to_add = rev_s.substr(k, n - k);
        
        cout << s + to_add << "\n";
    }
    
    return 0;
}
