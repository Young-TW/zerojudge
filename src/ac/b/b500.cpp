#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int n = s.length();
        vector<string> substrings;
        substrings.reserve(n * (n + 1) / 2);
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                substrings.push_back(s.substr(i, j - i));
            }
        }
        
        sort(substrings.begin(), substrings.end());
        substrings.erase(unique(substrings.begin(), substrings.end()), substrings.end());
        
        for (const string& sub : substrings) {
            cout << sub << '\n';
        }
    }
    
    return 0;
}
