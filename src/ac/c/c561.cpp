#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        int max_val = -1;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            int rev_a = 0;
            while (a > 0) {
                rev_a = rev_a * 10 + a % 10;
                a /= 10;
            }
            if (rev_a > max_val) {
                max_val = rev_a;
            }
        }
        cout << max_val << "\n";
    }
    return 0;
}
