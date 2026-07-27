#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // pre‑compute orthogonal neighbours for cells 1..9
    vector<int> neigh[10];               // 1‑based
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    for (int cell = 1; cell <= 9; ++cell) {
        int r = (cell - 1) / 3;
        int c = (cell - 1) % 3;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
                int nb = nr * 3 + nc + 1;
                neigh[cell].push_back(nb);
            }
        }
    }

    int n;
    if (!(cin >> n)) return 0;
    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;
        vector<int> ans;
        for (int mine = 1; mine <= 9; ++mine) {
            bool adjA = find(neigh[mine].begin(), neigh[mine].end(), a) != neigh[mine].end();
            bool adjB = find(neigh[mine].begin(), neigh[mine].end(), b) != neigh[mine].end();
            bool adjC = find(neigh[mine].begin(), neigh[mine].end(), c) != neigh[mine].end();
            if (adjA && !adjB && !adjC) ans.push_back(mine);
        }
        if (ans.empty()) {
            cout << "Empty\n";
        } else {
            for (size_t i = 0; i < ans.size(); ++i) {
                if (i) cout << ' ';
                cout << ans[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
