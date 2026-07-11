#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long N, M;
    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;
        
        if (M > N - M) {
            M = N - M;
        }
        
        long long ans = 1;
        for (long long i = 1; i <= M; ++i) {
            ans = ans * (N - M + i) / i;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
