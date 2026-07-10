#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        int maxRun = 0;
        int cur = 0;
        for (char c : line) {
            if (c == ' ') {
                ++cur;
                if (cur > maxRun) maxRun = cur;
            } else {
                cur = 0;
            }
        }
        int ans = 0;
        int k = maxRun;
        while (k > 1) {
            k = (k + 1) / 2; // ceil(k/2)
            ++ans;
        }
        cout << ans << "\n";
    }
    return 0;
}
