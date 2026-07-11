#include <iostream>
#include <vector>

using namespace std;

void dfs(int n, int start, vector<int>& current, vector<vector<int>>& ans) {
    for (int i = start; i * i <= n; ++i) {
        if (n % i == 0) {
            current.push_back(i);
            dfs(n / i, i, current, ans);
            
            vector<int> fact = current;
            fact.push_back(n / i);
            ans.push_back(fact);
            
            current.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n != 0) {
        vector<vector<int>> ans;
        vector<int> current;
        
        if (n > 1) {
            dfs(n, 2, current, ans);
        }
        
        cout << ans.size() << "\n";
        for (const auto& v : ans) {
            for (size_t i = 0; i < v.size(); ++i) {
                if (i > 0) cout << " ";
                cout << v[i];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
