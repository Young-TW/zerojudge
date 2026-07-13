#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b;
    while (cin >> a >> b) {
        int max_sum = a + b;
        int ans = 1;
        for (int i = 2; i <= 7; ++i) {
            cin >> a >> b;
            int sum = a + b;
            if (sum > max_sum) {
                max_sum = sum;
                ans = i;
            }
        }
        if (max_sum > 8) {
            cout << ans << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
    
    return 0;
}
