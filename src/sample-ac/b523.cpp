#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    unordered_set<string> seen;
    
    while (getline(cin, s)) {
        if (!s.empty() && s.back() == '\r') {
            s.pop_back();
        }
        
        if (seen.count(s)) {
            cout << "YES\n";
        } else {
            seen.insert(s);
            cout << "NO\n";
        }
    }
    
    return 0;
}
