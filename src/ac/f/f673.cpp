#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> L, R;

int dfs(int u) {
    if (u == -1) return -1;
    return 1 + max(dfs(L[u]), dfs(R[u]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        L.resize(N);
        R.resize(N);
        for (int i = 0; i < N; ++i) {
            int u, a, b;
            cin >> u >> a >> b;
            L[u] = a;
            R[u] = b;
        }
        cout << dfs(0) << "\n";
    }
    return 0;
}
