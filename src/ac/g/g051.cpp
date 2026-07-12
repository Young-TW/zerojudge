#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<long long> X(N), Y(N);
        for (int i = 0; i < N; i++) {
            cin >> X[i] >> Y[i];
        }
        
        int ans = 1;
        
        if (N <= 300) {
            for (int i = 0; i < N; i++) {
                for (int j = i + 1; j < N; j++) {
                    long long x1 = X[i], y1 = Y[i];
                    long long x2 = X[j], y2 = Y[j];
                    long long dx = x2 - x1;
                    long long dy = y2 - y1;
                    int cnt = 0;
                    for (int k = 0; k < N; k++) {
                        long long x3 = X[k] - x1;
                        long long y3 = Y[k] - y1;
                        if ((__int128)dy * x3 == (__int128)dx * y3) {
                            cnt++;
                        }
                    }
                    if (cnt > ans) {
                        ans = cnt;
                    }
                }
            }
            cout << ans << "\n";
            continue;
        }
        
        static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        int iters = 350;
        for (int iter = 0; iter < iters; iter++) {
            int i = rng() % N;
            int j = rng() % N;
            while (i == j) j = rng() % N;
            long long x1 = X[i], y1 = Y[i];
            long long x2 = X[j], y2 = Y[j];
            long long dx = x2 - x1;
            long long dy = y2 - y1;
            int cnt = 0;
            for (int k = 0; k < N; k++) {
                long long x3 = X[k] - x1;
                long long y3 = Y[k] - y1;
                if ((__int128)dy * x3 == (__int128)dx * y3) {
                    cnt++;
                }
            }
            if (cnt > ans) {
                ans = cnt;
            }
        }
        
        cout << ans << "\n";
    }
    return 0;
}
