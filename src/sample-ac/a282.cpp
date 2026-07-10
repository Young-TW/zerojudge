#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<char> seen(2001, 0);
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (x >= 1 && x <= 2000) seen[x] = 1;
        }
        int ans = 1;
        while (ans <= 2000 && seen[ans]) ++ans;
        cout << ans << "\n";
    }
    return 0;
}
