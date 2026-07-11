#include <iostream>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long S1, S2, S3;
    while (cin >> S1 >> S2 >> S3) {
        long long sum = S1 + S2 + S3;
        long long val = sum * sum - 4 * S1 * S3;
        
        long long ans = sqrt(val);
        while (ans * ans > val) {
            ans--;
        }
        while ((ans + 1) * (ans + 1) <= val) {
            ans++;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
