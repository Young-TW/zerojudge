#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long S1, S2, T, K;
    while (cin >> S1 >> S2 >> T >> K) {
        long long D = S2 - S1;
        long long S2K = S2 * K;
        long long S1K = S1 * K;
        
        if (S2K > T && T > S1K && (S2K - T) % D == 0) {
            long long Q1 = (S2K - T) / D;
            long long Q2 = K - Q1;
            cout << Q1 << " " << Q2 << "\n";
        } else {
            cout << "impossible\n";
        }
    }
    
    return 0;
}
