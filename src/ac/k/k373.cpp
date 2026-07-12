#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string name;
    int status;
    unordered_set<string> seen;
    vector<string> ans;
    
    while (cin >> name >> status) {
        if (status == 0) {
            if (seen.find(name) == seen.end()) {
                seen.insert(name);
                ans.push_back(name);
            }
        }
    }
    
    for (size_t i = 0; i < ans.size(); ++i) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}
