#include <iostream>

using namespace std;

bool check(int n, int m) {
    int r = n - 1;
    int pos = 0;
    while (r > 1) {
        pos = (pos + m - 1) % r;
        if (pos == 0) return false;
        r--;
    }
    return true;
}

int main() {
    int ans[150];
    for (int n = 3; n < 150; ++n) {
        for (int m = 1; ; ++m) {
            if (check(n, m)) {
                ans[n] = m;
                break;
            }
        }
    }
    
    int n;
    while (cin >> n) {
        if (n == 0) break;
        cout << ans[n] << endl;
    }
    return 0;
}
