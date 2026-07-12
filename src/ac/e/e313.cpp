#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        string ans;
        int min_distinct = 27;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            bool seen[26] = {false};
            int distinct = 0;
            for (char c : s) {
                if (!seen[c - 'A']) {
                    seen[c - 'A'] = true;
                    distinct++;
                }
            }
            if (distinct < min_distinct) {
                min_distinct = distinct;
                ans = s;
            } else if (distinct == min_distinct) {
                if (s < ans) {
                    ans = s;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
