#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    while (cin >> n >> m >> k) {
        vector<bool> has_key(m, false);
        queue<int> q;
        
        int t;
        cin >> t;
        for (int i = 0; i < t; ++i) {
            int key;
            cin >> key;
            if (!has_key[key]) {
                has_key[key] = true;
                q.push(key);
            }
        }
        
        vector<vector<int>> req(m);
        vector<int> need(n, k);
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                int r;
                cin >> r;
                req[r].push_back(i);
            }
        }
        
        vector<vector<int>> reward(n);
        for (int i = 0; i < n; ++i) {
            reward[i].resize(k);
            for (int j = 0; j < k; ++j) {
                cin >> reward[i][j];
            }
        }
        
        int opened_count = 0;
        
        while (!q.empty()) {
            int key = q.front();
            q.pop();
            
            for (int box : req[key]) {
                need[box]--;
                if (need[box] == 0) {
                    opened_count++;
                    for (int new_key : reward[box]) {
                        if (!has_key[new_key]) {
                            has_key[new_key] = true;
                            q.push(new_key);
                        }
                    }
                }
            }
        }
        
        cout << opened_count << "\n";
    }
    
    return 0;
}
