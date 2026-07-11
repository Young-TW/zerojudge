#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int n = s.length();
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }
        string ans(n, ' ');
        for (int i = 0; i < n; ++i) {
            ans[p[i] - 1] = s[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
