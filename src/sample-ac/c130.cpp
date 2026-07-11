#include <iostream>
#include <vector>

using namespace std;

int t, n;
int x[15];
bool found;

void dfs(int start, int sum, vector<int>& path) {
    if (sum == t) {
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) cout << "+";
            cout << path[i];
        }
        cout << "\n";
        found = true;
        return;
    }
    if (sum > t) return;
    
    for (int i = start; i < n; ++i) {
        if (i > start && x[i] == x[i-1]) continue;
        path.push_back(x[i]);
        dfs(i + 1, sum + x[i], path);
        path.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> t >> n && (t || n)) {
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }
        cout << "Sums of " << t << ":\n";
        found = false;
        vector<int> path;
        dfs(0, 0, path);
        if (!found) {
            cout << "NONE\n";
        }
    }
    
    return 0;
}
