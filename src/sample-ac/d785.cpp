#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool dfs(int idx, int n, int L, const vector<int>& sticks, vector<int>& groups) {
    if (idx == (int)sticks.size()) {
        return true;
    }
    vector<bool> visited(L + 1, false);
    for (int j = 0; j < n; ++j) {
        if (visited[groups[j]]) continue;
        if (groups[j] + sticks[idx] > L) continue;
        
        visited[groups[j]] = true;
        groups[j] += sticks[idx];
        if (dfs(idx + 1, n, L, sticks, groups)) return true;
        groups[j] -= sticks[idx];
        
        if (groups[j] == 0) break;
        if (groups[j] + sticks[idx] == L) break;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int n, m;
        if (!(cin >> n >> m)) break;
        
        vector<int> sticks(m);
        int sum = 0;
        for (int i = 0; i < m; ++i) {
            cin >> sticks[i];
            sum += sticks[i];
        }
        
        if (sum % n != 0) {
            cout << 0 << "\n";
            continue;
        }
        
        int L = sum / n;
        sort(sticks.begin(), sticks.end(), greater<int>());
        
        if (sticks[0] > L) {
            cout << 0 << "\n";
            continue;
        }
        
        vector<int> groups(n, 0);
        if (dfs(0, n, L, sticks, groups)) {
            cout << 1 << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
    
    return 0;
}
