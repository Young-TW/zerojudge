#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<long long> arr;
vector<long long> current;

void dfs(int cnt, int start) {
    if (cnt == m) {
        for (int i = 0; i < m; ++i) {
            cout << current[i];
            if (i < m - 1) cout << " ";
        }
        cout << "\n";
        return;
    }
    for (int i = start; i < n; ++i) {
        if (i > start && arr[i] == arr[i - 1]) continue;
        current.push_back(arr[i]);
        dfs(cnt + 1, i + 1);
        current.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n >> m && (n || m)) {
        arr.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end());
        dfs(0, 0);
    }
    return 0;
}
