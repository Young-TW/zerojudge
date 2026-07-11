#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    while (cin >> s) {
        int n = s.length();
        vector<int> first_pos(3 * n + 5, -1);
        int offset = n + 2;
        int prefix_sum = 0;
        first_pos[offset + prefix_sum] = 0;
        int last_S_pos = -1;
        int ans = -1;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'S') {
                if (first_pos[offset + prefix_sum] == -1) {
                    first_pos[offset + prefix_sum] = i;
                }
                prefix_sum += 2;
                last_S_pos = i + 1;
            } else if (s[i] == 'K') {
                if (first_pos[offset + prefix_sum] == -1) {
                    first_pos[offset + prefix_sum] = i;
                }
                prefix_sum -= 1;
            } else {
                if (first_pos[offset + prefix_sum] == -1) {
                    first_pos[offset + prefix_sum] = i;
                }
            }
            
            if (last_S_pos != -1 && first_pos[offset + prefix_sum] != -1 && first_pos[offset + prefix_sum] < last_S_pos) {
                ans = max(ans, (i + 1) - first_pos[offset + prefix_sum]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
