#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    int caseNum = 0;
    while (cin >> t) {
        while (t--) {
            int n, m;
            long long k;
            cin >> n >> k >> m;
            
            int start = n - m + 1;
            long long x = (k - 1) % start;
            int s = start;
            
            while (s < n) {
                if (k == 1) {
                    x += n - s;
                    break;
                }
                long long j = (long long)(s - 1 - x) / (k - 1);
                if (j < 1) {
                    x = (x + k) % (s + 1);
                    s++;
                } else {
                    if (j > n - s) j = n - s;
                    x = x + j * k;
                    s += (int)j;
                }
            }
            
            cout << "Case " << ++caseNum << ": " << x + 1 << "\n";
        }
    }
    return 0;
}
