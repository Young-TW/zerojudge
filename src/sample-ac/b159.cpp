#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int w;
    while (cin >> w) {
        int n;
        if (!(cin >> n)) break;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }
        sort(p.begin(), p.end());
        int left = 0, right = n - 1;
        int ans = 0;
        while (left <= right) {
            if (left == right) {
                ans++;
                break;
            }
            if (p[left] + p[right] <= w) {
                left++;
                right--;
                ans++;
            } else {
                right--;
                ans++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
