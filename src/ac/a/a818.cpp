#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<int> seq(n);
        for (int i = 0; i < n; ++i) {
            cin >> seq[i];
        }
        
        string s;
        cin >> s;
        
        long long k;
        cin >> k;

        vector<int> next_pos(n);
        for (int i = 0; i < n; ++i) {
            next_pos[i] = seq[i] - 1;
        }

        vector<bool> visited(n, false);
        string ans(n, ' ');

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                vector<int> cycle;
                int curr = i;
                while (!visited[curr]) {
                    visited[curr] = true;
                    cycle.push_back(curr);
                    curr = next_pos[curr];
                }

                int cycle_len = cycle.size();
                long long shift = k % cycle_len;
                
                for (int j = 0; j < cycle_len; ++j) {
                    int target_idx = cycle[(j + shift) % cycle_len];
                    ans[cycle[j]] = s[target_idx];
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
