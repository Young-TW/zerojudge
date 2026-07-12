#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        int ans = 0;
        bool prev_selected = false;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if (a == 1 && !prev_selected) {
                ans++;
                prev_selected = true;
            } else {
                prev_selected = false;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
