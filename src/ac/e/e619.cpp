#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        set<string> palindromes;
        int n = s.length();
        
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                bool isPal = true;
                int l = i, r = j;
                while (l < r) {
                    if (s[l] != s[r]) {
                        isPal = false;
                        break;
                    }
                    l++;
                    r--;
                }
                if (isPal) {
                    palindromes.insert(s.substr(i, j - i + 1));
                }
            }
        }
        
        cout << "The string '" << s << "' contains " << palindromes.size() << " palindromes.\n";
    }
    
    return 0;
}
