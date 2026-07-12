#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line1, line2;
    while (getline(cin, line1)) {
        if (line1.empty()) continue;
        if (!getline(cin, line2)) break;
        
        stringstream ss1(line1);
        vector<string> names;
        string name;
        while (ss1 >> name) {
            names.push_back(name);
        }
        
        stringstream ss2(line2);
        vector<int> pos(names.size());
        for (size_t i = 0; i < names.size(); ++i) {
            ss2 >> pos[i];
        }
        
        vector<string> ans(names.size());
        for (size_t i = 0; i < names.size(); ++i) {
            ans[pos[i] - 1] = names[i];
        }
        
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i > 0) cout << " ";
            cout << ans[i];
        }
        cout << "\n";
    }
    
    return 0;
}
