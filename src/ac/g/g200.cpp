#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <utility>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string root;
    int n, m;
    cin >> root >> n >> m;
    
    unordered_map<string, vector<string>> children;
    
    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        children[a].push_back(b);
    }
    
    vector<vector<string>> genPeople;
    
    stack<pair<string, int>> stk;
    stk.push(make_pair(root, 1));
    
    while (!stk.empty()) {
        pair<string, int> top = stk.top();
        stk.pop();
        
        string node = top.first;
        int gen = top.second;
        
        if (gen >= (int)genPeople.size()) {
            genPeople.resize(gen + 1);
        }
        genPeople[gen].push_back(node);
        
        vector<string>& ch = children[node];
        for (int i = (int)ch.size() - 1; i >= 0; i--) {
            stk.push(make_pair(ch[i], gen + 1));
        }
    }
    
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        if (k >= 1 && k < (int)genPeople.size()) {
            for (size_t j = 0; j < genPeople[k].size(); j++) {
                if (j > 0) cout << " ";
                cout << genPeople[k][j];
            }
        }
        cout << "\n";
    }
    
    return 0;
}
