#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long a;
    while (cin >> a) {
        long long target = a * a + 1;
        long long limit = (long long)sqrt((double)target);
        
        while (limit * limit > target) {
            limit--;
        }
        while ((limit + 1) * (limit + 1) <= target) {
            limit++;
        }
        
        long long x;
        for (x = limit; x >= 1; --x) {
            if (target % x == 0) {
                break;
            }
        }
        
        long long y = target / x;
        long long ans = x + y + 2 * a;
        cout << ans << "\n";
    }
    
    return 0;
}
