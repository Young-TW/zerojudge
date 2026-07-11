#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

long long power(long long base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; ++i) {
        res *= base;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (!(cin >> t)) return 0;
    
    const double PI = acos(-1.0);
    
    while (t--) {
        int n;
        cin >> n;
        vector<long long> f(n + 1, 0);
        for (int i = 0; i <= n; ++i) {
            cin >> f[n - i];
        }
        long long a, b;
        cin >> a >> b;
        
        vector<long long> g(2 * n + 1, 0);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                g[i + j] += f[i] * f[j];
            }
        }
        
        double ans = 0.0;
        for (int i = 0; i <= 2 * n; ++i) {
            double term = (double)(g[i] * (power(b, i + 1) - power(a, i + 1))) / (i + 1);
            ans += term;
        }
        ans *= PI;
        
        cout << fixed << setprecision(2) << ans << "\n";
    }
    
    return 0;
}
