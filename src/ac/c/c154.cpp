#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> T(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> T[i];
        }
        
        vector<int> vis(n + 1, 0);
        vector<int> dist(n + 1, 0);
        int ans = n + 1;
        int timer = 0;
        
        for (int i = 1; i <= n; ++i) {
            if (vis[i] == 0) {
                int curr = i;
                timer++;
                int d = 1;
                while (vis[curr] == 0) {
                    vis[curr] = timer;
                    dist[curr] = d;
                    curr = T[curr];
                    d++;
                }
                if (vis[curr] == timer) {
                    int cycle_len = d - dist[curr];
                    if (cycle_len < ans) {
                        ans = cycle_len;
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
