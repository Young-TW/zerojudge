#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k, target;
vector<int> arr;

bool dfs(int idx, int picked, int current_sum) {
    if (picked == k) return current_sum == target;
    if (idx == n) return false;
    if (current_sum > target) return false;
    if (n - idx < k - picked) return false;
    
    if (dfs(idx + 1, picked + 1, current_sum + arr[idx])) return true;
    if (dfs(idx + 1, picked, current_sum)) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> n >> k >> target) {
        arr.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end(), greater<int>());
        
        if (dfs(0, 0, 0)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
