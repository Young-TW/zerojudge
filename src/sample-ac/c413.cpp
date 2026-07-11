#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    long long K;
    
    while (cin >> N >> K) {
        vector<long long> A(N);
        vector<long long> B(N);
        
        for (int i = 0; i < N; ++i) {
            cin >> A[i] >> B[i];
        }
        
        long long ans = 0;
        
        // Lambda function to calculate the total efficiency for a given target X
        auto calculate_sum = [&](long long X) {
            long long sum = 0;
            for (int i = 0; i < N; ++i) {
                if ((A[i] & X) == X) {
                    sum += B[i];
                }
            }
            return sum;
        };
        
        // Case 1: Target is exactly K
        ans = max(ans, calculate_sum(K));
        
        // Case 2: Target is strictly greater than K
        // We iterate through each bit position. If K has a 0 at bit b,
        // we can construct a valid X by setting bit b to 1, keeping bits
        // above b the same as K, and setting bits below b to 0.
        // This X is guaranteed to be > K.
        for (int b = 0; b <= 62; ++b) {
            if (((K >> b) & 1) == 0) {
                long long X = ((K >> b) << b) | (1LL << b);
                ans = max(ans, calculate_sum(X));
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
