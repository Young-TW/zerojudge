#include <iostream>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long ans[501] = {0};
    for (int n = 2; n <= 500; ++n) {
        ans[n] = ans[n - 1];
        for (int i = 1; i < n; ++i) {
            ans[n] += gcd(i, n);
        }
    }
    
    int n;
    while (cin >> n && n) {
        cout << ans[n] << "\n";
    }
    
    return 0;
}
