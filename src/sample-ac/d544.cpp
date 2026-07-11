#include <iostream>

using namespace std;

unsigned long long L[105];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    L[1] = 1;
    L[2] = 1;
    for (int i = 3; i <= 100; ++i) {
        L[i] = L[i-1] + L[i-2];
        if (L[i] > 2000000000ULL) {
            L[i] = 2000000001ULL;
        }
    }
    
    int M;
    while (cin >> M) {
        while (M--) {
            int N;
            unsigned long long K;
            cin >> N >> K;
            
            int ans = -1;
            while (true) {
                if (N == 1) {
                    if (K == 1) ans = 0;
                    break;
                }
                if (N == 2) {
                    if (K == 1) ans = 1;
                    break;
                }
                if (K <= L[N-2]) {
                    N = N - 2;
                } else if (K <= L[N-2] + L[N-1]) {
                    K = K - L[N-2];
                    N = N - 1;
                } else {
                    break;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
