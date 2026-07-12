#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int M;
vector<int> sticks;
vector<bool> used;
int target;

bool dfs(int sides_completed, int current_len, int start_idx) {
    if (sides_completed == 3) return true;
    
    if (current_len == target) {
        return dfs(sides_completed + 1, 0, 0);
    }
    
    for (int i = start_idx; i < M; ++i) {
        if (used[i]) continue;
        if (current_len + sticks[i] > target) continue;
        
        if (i > 0 && sticks[i] == sticks[i-1] && !used[i-1]) continue;
        
        used[i] = true;
        if (dfs(sides_completed, current_len + sticks[i], i + 1)) {
            return true;
        }
        used[i] = false;
        
        if (current_len + sticks[i] == target) return false;
        if (current_len == 0) return false;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            cin >> M;
            sticks.resize(M);
            used.assign(M, false);
            for (int i = 0; i < M; ++i) {
                cin >> sticks[i];
            }
            
            int total = accumulate(sticks.begin(), sticks.end(), 0);
            if (total % 4 != 0) {
                cout << "no\n";
                continue;
            }
            target = total / 4;
            
            sort(sticks.begin(), sticks.end(), [](int a, int b) {
                return a > b;
            });
            
            if (sticks[0] > target) {
                cout << "no\n";
                continue;
            }
            
            if (dfs(0, 0, 0)) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }
    return 0;
}
