#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int R = 8000;
    const double A = 32767.0;
    const double PI = 3.14159265358979323846;
    
    long long F, T;
    while (cin >> F >> T) {
        long long N = static_cast<long long>(R) * T;
        cout << R << ' ' << N << '\n';
        for (long long i = 0; i < N; ++i) {
            double angle = 2.0 * PI * static_cast<double>(F) * static_cast<double>(i) / R;
            long long sample = llround(A * sin(angle));
            if (i) cout << ' ';
            cout << sample;
        }
        cout << '\n';
    }
    return 0;
}
