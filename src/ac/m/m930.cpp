#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    long long K;
    while (cin >> N >> K) {
        vector<long long> W(N), D(N);
        for (int i = 0; i < N; ++i) cin >> W[i];
        for (int i = 0; i < N; ++i) cin >> D[i];

        long long sumW = 0;
        long long Dmax = 0;
        for (int i = 0; i < N; ++i) {
            sumW += W[i];
            Dmax = max(Dmax, D[i]);
        }
        long double L = static_cast<long double>(sumW);          // side length

        // total capacity
        long double capacity = 0.0L;
        for (int i = 0; i < N; ++i) {
            capacity += static_cast<long double>(W[i]) * D[i];
        }
        capacity *= L;   // volume

        long double answer;
        if (static_cast<long double>(K) >= capacity) {
            answer = static_cast<long double>(Dmax);
        } else {
            // binary search on h in [0, Dmax]
            long double low = 0.0L, high = static_cast<long double>(Dmax);
            for (int iter = 0; iter < 80; ++iter) {
                long double mid = (low + high) * 0.5L;
                // compute volume for depth = mid
                long double vol = 0.0L;
                for (int i = 0; i < N; ++i) {
                    long double diff = static_cast<long double>(Dmax - D[i]);
                    if (mid > diff) {
                        vol += (mid - diff) * static_cast<long double>(W[i]);
                    }
                }
                vol *= L;
                if (vol >= static_cast<long double>(K))
                    high = mid;
                else
                    low = mid;
            }
            answer = high;
        }

        cout << fixed << setprecision(1) << static_cast<double>(answer) << '\n';
    }
    return 0;
}
