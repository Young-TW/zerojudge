#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> arr;
vector<int> cur;

void dfs(int idx, int cnt) {
    if (cnt == m) {
        for (int i = 0; i < m; ++i) {
            cout << cur[i];
            if (i < m - 1) cout << " ";
        }
        cout << "\n";
        return;
    }
    if (idx == n) return;
    
    cur.push_back(arr[idx]);
    dfs(idx + 1, cnt + 1);
    cur.pop_back();
    
    dfs(idx + 1, cnt);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> n && n != 0) {
        arr.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        cin >> m;
        sort(arr.begin(), arr.end());
        cur.clear();
        dfs(0, 0);
        cout << "\n";
    }
    return 0;
}
