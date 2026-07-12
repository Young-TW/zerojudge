#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, n;
    while (cin >> m >> n) {
        vector<string> members(m);
        for (int i = 0; i < m; ++i) {
            cin >> members[i];
        }
        
        unordered_set<string> attended;
        attended.reserve(n);
        string id;
        for (int i = 0; i < n; ++i) {
            cin >> id;
            attended.insert(id);
        }
        
        int absent = 0;
        for (int i = 0; i < m; ++i) {
            if (attended.find(members[i]) == attended.end()) {
                ++absent;
            }
        }
        
        cout << absent << "\n";
    }
    
    return 0;
}
