#include <iostream>

using namespace std;

const int MAXN = 1000000;
int ans[MAXN + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for (int k = 2; k * (k + 1) / 2 <= MAXN; ++k) {
        long long base = (long long)k * (k - 1) / 2;
        for (long long a = 1; ; ++a) {
            long long n = k * a + base;
            if (n > MAXN) break;
            ans[n]++;
        }
    }
    
    int n;
    while (cin >> n && n) {
        cout << ans[n] << "\n";
    }
    
    return 0;
}
