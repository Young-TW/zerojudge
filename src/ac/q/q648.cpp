#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end(), greater<int>());
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] >= i + 1) {
                ans = i + 1;
            } else {
                break;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
