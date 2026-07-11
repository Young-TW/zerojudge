#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long M, K;
    while (cin >> M >> K) {
        long long cnt = 0;
        for (long long i = 0; i < K; ++i) {
            long long t;
            cin >> t;
            long long r = t % M;
            if (r == 0 || r == 1 || r == M - 1) {
                ++cnt;
            }
        }
        cout << cnt << "\n";
    }
    
    return 0;
}
