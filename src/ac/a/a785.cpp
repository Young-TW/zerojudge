#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // contraction table: root vowel -> (suffix vowel -> result)
    map<char, map<string, string>> tbl;
    // row for 'a'
    tbl['a'] = {
        {"a", "a"},
        {"e", "y"},
        {"i", "ai"},
        {"y", "a"},
        {"o", "w"},
        {"ou","w"},
        {"w", "w"}
    };
    // row for 'e'
    tbl['e'] = {
        {"a", "y"},
        {"e", "ei"},
        {"i", "ei"},
        {"y", "y"},
        {"o", "ou"},
        {"ou","ou"},
        {"w", "w"}
    };
    // row for 'o'
    tbl['o'] = {
        {"a", "w"},
        {"e", "ou"},
        {"i", "oi"},
        {"y", "w"},
        {"o", "ou"},
        {"ou","ou"},
        {"w", "w"}
    };
    
    string line;
    while (cin >> line) {
        if (line == "END") break;
        size_t dash = line.find('-');
        string root = line.substr(0, dash);
        string suffix = line.substr(dash + 1);
        
        char r = root.back();                     // last vowel of root
        string s;                                 // first vowel of suffix
        if (suffix.size() >= 2 && suffix[0] == 'o' && suffix[1] == 'u')
            s = "ou";
        else
            s = string(1, suffix[0]);
        
        string repl = tbl[r][s];                  // contracted part
        
        string ans = root.substr(0, root.size() - 1)   // root without last vowel
                     + repl
                     + suffix.substr(s.size());       // suffix without its first vowel
        cout << ans << '\n';
    }
    return 0;
}
