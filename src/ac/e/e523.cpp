#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAXM = 1000000;
    int ans[MAXM + 1];
    for (int i = 0; i <= MAXM; ++i) {
        ans[i] = -1;
    }
    
    long long f1 = 1, f2 = 1;
    ans[1] = 1;
    long long f3 = f1 + f2;
    int idx = 3;
    while (f3 <= MAXM) {
        if (ans[f3] == -1) {
            ans[f3] = idx;
        }
        f1 = f2;
        f2 = f3;
        f3 = f1 + f2;
        idx++;
    }
    
    int n;
    while (cin >> n) {
        while (n--) {
            int m;
            cin >> m;
            if (m >= 1 && m <= MAXM) {
                cout << ans[m] << "\n";
            } else {
                cout << -1 << "\n";
            }
        }
    }
    
    return 0;
}
