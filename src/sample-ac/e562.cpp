#include <iostream>

using namespace std;

const int MAXN = 1000001;
long long ans[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ans[3] = 0;
    for (long long i = 4; i < MAXN; ++i) {
        if (i % 2 == 0) {
            ans[i] = ans[i - 1] + (i - 2) * (i - 2) / 4;
        } else {
            ans[i] = ans[i - 1] + (i - 1) * (i - 3) / 4;
        }
    }
    
    int n;
    while (cin >> n && n) {
        cout << ans[n] << "\n";
    }
    
    return 0;
}
